# libSceVideoRecording.native technical debt

### Additional callable exports

- [Additional callable exports](../../../core/libs/prx/libSceVideoRecording.native/Export.cpp) - 27 entries observed in the 3.20 export inventory and present in the later 13.60-labelled inventory are import-resolution declarations only. The later inventory label does not authenticate a retail firmware version. Parameter lists, return types and behavior are unverified; parameterless `int` declarations are placeholders, not verified ABI contracts. Every entry throws through `NotImplemented_nid_no_patch`. Unidentified names use literal NID aliases. No runtime functionality is implemented. Identified candidate names match their NIDs in the [public symbol database](https://github.com/zecoxao/sce_symbols/blob/2883963a0a514ba6e77407a08ef4730a65e88254/aerolib.csv) or [supplemental catalog](https://github.com/claimore22/ps5rs/blob/2304be5131221bae0dac24b9767cabffda33f747/data/nids.csv).

[Version-pinned selected ELF export records](https://gist.github.com/kyon-eth/752e1b1d4a6ac8a26c97e693527fefbd/6a60d79146e8960fe6da14716d2b38055db04228) list every NID below with its module, raw qualified symbol, ELF function type, value and size for each inspected version-labelled module. The extract SHA-256 is `52357fe6274f0b5057b20f12d4e3ba5446161db8d9aac0c926beed1dd22b0bbd`; its full-module sorted-function-NID digests and raw module-parameter words permit independent comparison. The extract is an analyst-produced metadata record, not independent authentication of the original images or proof of prototypes or behavior. The separately published 3.20 source catalog has a module file but none of these selected NIDs.

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
