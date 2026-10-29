# libSceVideoRecording.native technical debt

### Additional callable exports

- [Additional callable exports](../../../core/libs/prx/libSceVideoRecording.native/Export.cpp) - 27 entries observed in the 3.20 export inventory and present in the later 13.60-labelled inventory are import-resolution declarations only. The later inventory label does not authenticate a retail firmware version. Parameter lists, return types and behavior are unverified; parameterless `int` declarations are placeholders, not verified ABI contracts. Every entry throws through `NotImplemented_nid_no_patch`. Unidentified names use literal NID aliases. No runtime functionality is implemented. Identified candidate names match their NIDs in the [public symbol database](https://github.com/zecoxao/sce_symbols/blob/2883963a0a514ba6e77407a08ef4730a65e88254/aerolib.csv) or [supplemental catalog](https://github.com/claimore22/ps5rs/blob/2304be5131221bae0dac24b9767cabffda33f747/data/nids.csv).

| Name | NID |
| --- | --- |
| `sceVideoRecordingCopyBGRAtoP010` | `X1f4SXr5qQY` |
| `sceVideoRecordingDisableScanInEncode` | `byQbu2Mg3DI` |
| `sceVideoRecordingEnableScanInEncode` | `taRss8qdZ9Y` |
| `sceVideoRecordingFinalizeByAppId` | `8edDi-bYdbU` |
| `sceVideoRecordingFinalizeByHandle` | `vQFaqjQmdnw` |
| `sceVideoRecordingGetCountScanInAction` | `qUqHoCwWgjE` |
| `sceVideoRecordingGetFinalizeActiveInfo` | `lplCnUFaGm4` |
| `sceVideoRecordingGetFormatByAppId` | `xNcqZLKU9Wk` |
| `sceVideoRecordingGetFormatExtensionByAppId` | `XJoIh8Asbbk` |
| `sceVideoRecordingGetRecordedDurationByAppId` | `WK59GBCCc6k` |
| `sceVideoRecordingGetRecordedDurationByHandle` | `zepTKsV7mmE` |
| `sceVideoRecordingGetStatusByAppId` | `DA6qMJMGP+U` |
| `sceVideoRecordingGetStatusByHandle` | `ufwOTTG2jV4` |
| `sceVideoRecordingIsProfileChangeSupported` | `AyI9L0Dxm+4` |
| `sceVideoRecordingOpenByRAFeatureId` | `qEfkBZEwu7g` |
| `sceVideoRecordingResetRecordedData` | `oWf+aK9v1Pw` |
| `sceVideoRecordingRestModeProcessStop` | `F8pia9FXpPs` |
| `sceVideoRecordingSetCopyrightImage` | `Augrd4cY6E0` |
| `sceVideoRecordingSetInfoByHandle` | `PmqSOAzftJg` |
| `sceVideoRecordingSetPrivacyImage` | `nzmFH8Adz5c` |
| `sceVideoRecordingSetProfileLimit` | `kEfdObutIDg` |
| `sceVideoRecordingSetResourceStateByHandle` | `BebkD-x+vZc` |
| `sceVideoRecordingStartByHandle` | `ypNPzNhXzRg` |
| `sceVideoRecordingStopByHandle` | `mopHCpOSZT8` |
| `Unknown` | `26XG0o9fx8Q` |
| `Unknown` | `WT4aTfe5OYk` |
| `Unknown` | `iYtbtBx4jvE` |
