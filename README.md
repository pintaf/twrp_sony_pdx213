# TWRP device tree for Xperia 10 III (Lena/pdx213)

No need to add a kernek repo, it is budnle in this tree under it's precompiled form

## Features

Works:

- To be defined

## To-do
- A lot

## Compile

First checkout minimal twrp with aosp tree:

```
repo init -u https://github.com/minimal-manifest-twrp/platform_manifest_twrp_aosp -b twrp-12.1
```

Create the folder `.repo/local_manifests`,  followed by a file file `.repo/local_manifests/my_manifest.xml` with this content:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
    <project path="device/sony/pdx213" name="pintaf/android_twrp_device_sony_pdx213" remote="github" revision="main" />
</manifest>
```
Do a `repo sync`


Finally execute these:


```
. build/envsetup.sh
lunch twrp_pdx213-eng
mka recoveryimage
```

To test it:

```
fastboot flash out/target/product/pdx213/recovery.img
```




## Thanks
- [sekaiacg](https://github.com/sekaiacg/device_xiaomi_alioth-TWRP/) for twrp base
- [ShirokaneShizuku](https://github.com/ShirokaneShizuku) for initial bringup
- [hellobbn](https://github.com/hellobbn/) for kernel source
