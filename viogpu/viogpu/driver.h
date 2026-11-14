/*
 * Copyright (C) 2019-2022 Red Hat, Inc.
 *
 * Written By: Vadim Rozenfeld <vrozenfe@redhat.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met :
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and / or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of their contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#pragma once
#include "helper.h"

extern "C" DRIVER_INITIALIZE DriverEntry;

VOID VioGpuUnload(VOID);

NTSTATUS
VioGpuAddDevice(_In_ DEVICE_OBJECT *pPhysicalDeviceObject, _Outptr_ PVOID *ppDeviceContext);

NTSTATUS
VioGpuRemoveDevice(_In_ VOID *pDeviceContext);

NTSTATUS
VioGpuStartDevice(_In_ VOID *pDeviceContext,
                     _In_ DXGK_START_INFO *pDxgkStartInfo,
                     _In_ DXGKRNL_INTERFACE *pDxgkInterface,
                     _Out_ ULONG *pNumberOfViews,
                     _Out_ ULONG *pNumberOfChildren);

NTSTATUS
VioGpuStopDevice(_In_ VOID *pDeviceContext);

VOID VioGpuResetDevice(_In_ VOID *pDeviceContext);

NTSTATUS
VioGpuDispatchIoRequest(_In_ VOID *pDeviceContext,
                           _In_ ULONG VidPnSourceId,
                           _In_ VIDEO_REQUEST_PACKET *pVideoRequestPacket);

NTSTATUS
VioGpuSetPowerState(_In_ VOID *pDeviceContext,
                       _In_ ULONG HardwareUid,
                       _In_ DEVICE_POWER_STATE DevicePowerState,
                       _In_ POWER_ACTION ActionType);

NTSTATUS
VioGpuQueryChildRelations(_In_ VOID *pDeviceContext,
                             _Out_writes_bytes_(ChildRelationsSize) DXGK_CHILD_DESCRIPTOR *pChildRelations,
                             _In_ ULONG ChildRelationsSize);

NTSTATUS
VioGpuQueryChildStatus(_In_ VOID *pDeviceContext,
                          _Inout_ DXGK_CHILD_STATUS *pChildStatus,
                          _In_ BOOLEAN NonDestructiveOnly);

NTSTATUS
VioGpuQueryDeviceDescriptor(_In_ VOID *pDeviceContext,
                               _In_ ULONG ChildUid,
                               _Inout_ DXGK_DEVICE_DESCRIPTOR *pDeviceDescriptor);

BOOLEAN
VioGpuInterruptRoutine(_In_ VOID *pDeviceContext, _In_ ULONG MessageNumber);

VOID VioGpuDpcRoutine(_In_ VOID *pDeviceContext);

NTSTATUS
APIENTRY
VioGpuQueryAdapterInfo(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_QUERYADAPTERINFO *pQueryAdapterInfo);

NTSTATUS
APIENTRY
VioGpuSetPointerPosition(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_SETPOINTERPOSITION *pSetPointerPosition);

NTSTATUS
APIENTRY
VioGpuSetPointerShape(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_SETPOINTERSHAPE *pSetPointerShape);

NTSTATUS
APIENTRY
VioGpuEscape(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_ESCAPE *pEscape);

NTSTATUS
VioGpuQueryInterface(_In_ CONST PVOID pDeviceContext, _In_ CONST PQUERY_INTERFACE pQueryInterface);

NTSTATUS
APIENTRY
VioGpuPresentDisplayOnly(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_PRESENT_DISPLAYONLY *pPresentDisplayOnly);

NTSTATUS
APIENTRY
VioGpuIsSupportedVidPn(_In_ CONST HANDLE hAdapter, _Inout_ DXGKARG_ISSUPPORTEDVIDPN *pIsSupportedVidPn);

NTSTATUS
APIENTRY
VioGpuRecommendFunctionalVidPn(_In_ CONST HANDLE hAdapter,
                                  _In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN *CONST pRecommendFunctionalVidPn);

NTSTATUS
APIENTRY
VioGpuRecommendVidPnTopology(_In_ CONST HANDLE hAdapter,
                                _In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY *CONST pRecommendVidPnTopology);

NTSTATUS
APIENTRY
VioGpuRecommendMonitorModes(_In_ CONST HANDLE hAdapter,
                               _In_ CONST DXGKARG_RECOMMENDMONITORMODES *CONST pRecommendMonitorModes);

NTSTATUS
APIENTRY
VioGpuEnumVidPnCofuncModality(_In_ CONST HANDLE hAdapter,
                                 _In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY *CONST pEnumCofuncModality);

NTSTATUS
APIENTRY
VioGpuSetVidPnSourceVisibility(_In_ CONST HANDLE hAdapter,
                                  _In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY *pSetVidPnSourceVisibility);

NTSTATUS
APIENTRY
VioGpuCommitVidPn(_In_ CONST HANDLE hAdapter, _In_ CONST DXGKARG_COMMITVIDPN *CONST pCommitVidPn);

NTSTATUS
APIENTRY
VioGpuUpdateActiveVidPnPresentPath(_In_ CONST HANDLE hAdapter,
                                      _In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH *CONST pUpdateActiveVidPnPresentPath);

NTSTATUS
APIENTRY
VioGpuQueryVidPnHWCapability(_In_ CONST HANDLE hAdapter, _Inout_ DXGKARG_QUERYVIDPNHWCAPABILITY *pVidPnHWCaps);

NTSTATUS
APIENTRY
VioGpuStopDeviceAndReleasePostDisplayOwnership(_In_ VOID *pDeviceContext,
                                                  _In_ D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
                                                  _Out_ DXGK_DISPLAY_INFORMATION *DisplayInfo);

NTSTATUS
APIENTRY
VioGpuSystemDisplayEnable(_In_ VOID *pDeviceContext,
                             _In_ D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
                             _In_ PDXGKARG_SYSTEM_DISPLAY_ENABLE_FLAGS Flags,
                             _Out_ UINT *Width,
                             _Out_ UINT *Height,
                             _Out_ D3DDDIFORMAT *ColorFormat);

VOID APIENTRY VioGpuSystemDisplayWrite(_In_ VOID *pDeviceContext,
                                          _In_ VOID *Source,
                                          _In_ UINT SourceWidth,
                                          _In_ UINT SourceHeight,
                                          _In_ UINT SourceStride,
                                          _In_ UINT PositionX,
                                          _In_ UINT PositionY);
