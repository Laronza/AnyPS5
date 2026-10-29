# libfontconfig technical debt

### Callable exports

- [Callable exports](../../../core/libs/prx/libfontconfig/Export.cpp) - 53 entries are import-resolution declarations only. Parameter lists, return types and behavior are unverified; parameterless `int` declarations are placeholders, not verified ABI contracts. Every entry throws through `NotImplemented_nid_no_patch`. Unidentified names use literal NID aliases. No runtime functionality is implemented. Data exports require separate layout and ownership analysis. Candidate names match their NIDs in the [public symbol database](https://github.com/zecoxao/sce_symbols/blob/2883963a0a514ba6e77407a08ef4730a65e88254/aerolib.csv) or [supplemental catalog](https://github.com/claimore22/ps5rs/blob/2304be5131221bae0dac24b9767cabffda33f747/data/nids.csv).

| Name | NID |
| --- | --- |
| `FcLangSetDestroy` | `+6aV1q-CAIg` |
| `FcPatternRemove` | `+XnLLwt2q-Y` |
| `FcPatternGetInteger` | `2BFkLGmS+Ao` |
| `FcConfigGetCurrent` | `2M54M-SKV-k` |
| `FcPatternGetBool` | `3zWpyQga5N0` |
| `FcPatternAddBool` | `6LGRGSLdSdQ` |
| `FcFontList` | `7+Gq-0xFybo` |
| `FcFontSetMatch` | `8DLBHeMsS1k` |
| `FcConfigSubstitute` | `8v4Xk2b+C1k` |
| `FcPatternGetMatrix` | `9x04OJBX0J0` |
| `FcInit` | `AwGzFwnaitQ` |
| `FcInitBringUptoDate` | `Ck9k-L7rz-I` |
| `FcPatternGetString` | `CkZ778Hu6Ng` |
| `FcFontRenderPrepare` | `CvqQqWqcO-0` |
| `FcPatternAddDouble` | `D-WphAs+Lh8` |
| `FcPatternDuplicate` | `DPxdK61lRaE` |
| `FcFontMatch` | `FqneT2syjGE` |
| `FcPatternFilter` | `H9TOtqlqmHM` |
| `FcConfigCreate` | `HGtDYp4ddNE` |
| `FcPatternGetFTFace` | `HjlABSyLzNg` |
| `FcPatternEqual` | `HxFAszDPXuE` |
| `FcCharSetSubtractCount` | `J8GcxU03WkE` |
| `FcPatternAddInteger` | `LNzAovAnOd8` |
| `FcLangSetAdd` | `Lsu4XJJ3V2o` |
| `FcFontSort` | `MApHziT-St4` |
| `FcCharSetMerge` | `MafDsPXgY6k` |
| `FcPatternGetCharSet` | `NKrjlO4HBhg` |
| `FcCharSetDestroy` | `Nw0ilSm8FxY` |
| `FcPatternDel` | `Om2ww9GOmes` |
| `FcConfigDestroy` | `Oor7ukCXZOE` |
| `FcPatternReference` | `QZuEIDVT42s` |
| `FcObjectSetDestroy` | `WtTZKbENx4o` |
| `FcPatternGet` | `Xmsz9ffM-9g` |
| `FcPatternAddMatrix` | `Zqa5tqMhOrI` |
| `FcPatternAddString` | `bU30lh8YpkE` |
| `FcFontSetCreate` | `fJfx9D9g9W4` |
| `FcLangSetHasLang` | `gbtAblHLpQg` |
| `FcCharSetCreate` | `hNyN1seFzWY` |
| `FcLangSetCreate` | `jjz2C1StauM` |
| `FcFreeTypeCharIndex` | `l240XTbw2vk` |
| `FcFontSetAdd` | `lEIEcYhU2vE` |
| `FcPatternDestroy` | `nVkAFM4iCS4` |
| `FcCharSetAddChar` | `nXYd1oE9ZM0` |
| `FcMatrixMultiply` | `oM+8JNTrd24` |
| `FcPatternAddCharSet` | `paHcj4DoPQ4` |
| `FcDefaultSubstitute` | `sqEJZ2yMVNw` |
| `FcObjectSetBuild` | `v5-8NZmvyrA` |
| `FcPatternAddLangSet` | `vqX-PYS3MPc` |
| `FcFontSetDestroy` | `vrZNehbMgsU` |
| `FcPatternGetLangSet` | `x55q-bC-i+8` |
| `FcPatternCreate` | `xGAEbwA7FNo` |
| `FcConfigReference` | `yQed09jA3VA` |
| `FcPatternFormat` | `zqe0Dw9BCpc` |
