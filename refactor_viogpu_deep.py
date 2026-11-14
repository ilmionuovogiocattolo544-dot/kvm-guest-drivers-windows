import os
import re
import shutil

TARGET_DIR = "viogpu"

# Mappatura completa di sostituzione (case-sensitive, dall'identificatore più lungo al più corto)
REPLACEMENTS = [
    ("VioGpuDod_Service_Inst", "VioGpu_Service_Inst"),
    ("VioGpuDod_EventLog_Inst", "VioGpu_EventLog_Inst"),
    ("VioGpuDod_Inst", "VioGpu_Inst"),
    ("VioGpuDod.DeviceDesc", "VioGpu.DeviceDesc"),
    ("VioGpuDod.SVCDESC", "VioGpu.SVCDESC"),
    ("VIOGPUDO", "VIOGPU"),
    ("VioGpuDod", "VioGpu"),
    ("VioGpuDo", "VioGpu"),
    ("viogpudo", "viogpu"),
]

# Estensioni di codice sorgente, risorse, progetti e INF da riscrivere
TEXT_EXTENSIONS = {
    ".c", ".cpp", ".h", ".hpp", ".rc", ".mc", ".inx", ".inf",
    ".vcxproj", ".filters", ".props", ".targets", ".bat", ".ps1", ".cmd", ".def"
}

def refactor_content(text):
    for old, new in REPLACEMENTS:
        text = text.replace(old, new)
    return text

def process_tree(root_dir):
    if not os.path.isdir(root_dir):
        print(f"[ERRORE] Cartella '{root_dir}' non trovata. Esegui lo script dalla root del repo.")
        return

    # 1. Riscrittura profonda del contenuto dei file
    modified_files = 0
    for dirpath, _, filenames in os.walk(root_dir):
        for fname in filenames:
            ext = os.path.splitext(fname)[1].lower()
            if ext not in TEXT_EXTENSIONS:
                continue

            fpath = os.path.join(dirpath, fname)
            
            # Gestione encoding (i file .rc e .inx Windows spesso sono UTF-16LE o UTF-8)
            raw = open(fpath, "rb").read()
            encoding = "utf-8"
            if raw.startswith(b"\xff\xfe"):
                encoding = "utf-16-le"
            elif raw.startswith(b"\xfe\xff"):
                encoding = "utf-16-be"

            try:
                content = raw.decode(encoding)
            except UnicodeDecodeError:
                encoding = "latin-1"
                content = raw.decode(encoding)

            new_content = refactor_content(content)
            if new_content != content:
                with open(fpath, "wb") as f:
                    f.write(new_content.encode(encoding))
                modified_files += 1
                print(f"[CODICE AGGIORNATO] {fpath}")

    # 2. Rinomina file e directory residui (dal basso verso l'alto)
    renamed_items = 0
    for dirpath, dirnames, filenames in os.walk(root_dir, topdown=False):
        for fname in filenames:
            if "viogpudo" in fname.lower():
                old_p = os.path.join(dirpath, fname)
                new_fname = re.sub(r"viogpudo", "viogpu", fname, flags=re.IGNORECASE)
                new_p = os.path.join(dirpath, new_fname)
                if old_p != new_p:
                    if os.path.exists(new_p):
                        os.remove(new_p)
                    os.rename(old_p, new_p)
                    renamed_items += 1
                    print(f"[FILE RINOMINATO]   {old_p} -> {new_p}")

        for dname in dirnames:
            if "viogpudo" in dname.lower():
                old_d = os.path.join(dirpath, dname)
                new_dname = re.sub(r"viogpudo", "viogpu", dname, flags=re.IGNORECASE)
                new_d = os.path.join(dirpath, new_dname)
                if old_d != new_d:
                    if os.path.exists(new_d):
                        shutil.rmtree(new_d)
                    os.rename(old_d, new_d)
                    renamed_items += 1
                    print(f"[DIR RINOMINATA]    {old_d} -> {new_d}")

    print(f"\nCompletato: {modified_files} file di codice riscritti, {renamed_items} elementi rinominati.")

if __name__ == "__main__":
    process_tree(TARGET_DIR)
