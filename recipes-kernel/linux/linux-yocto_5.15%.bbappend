FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto:"

SRC_URI += " \
    file://edac.cfg \
    file://wdt-sp5100-tco.cfg \
"

# base on generic config from:
# http://git.yoctoproject.org/cgit/cgit.cgi/yocto-kernel-cache/tree/bsp/common-pc-64/common-pc-64.scc?h=yocto-4.14
KMACHINE:pcengines-apux = "common-pc-64"

# enable SMP
KERNEL_FEATURES:append:pcengines-apux = " \
    cfg/smp.scc \
"

# disable graphics and Intel CPU/GPU support
SRC_URI:append:pcengines-apux = " file://disable-graphics.cfg"
KERNEL_FEATURES:remove:pcengines-apux = " \
    cfg/intel.scc \
    features/i915/i915.scc \
    features/usb/touchscreen-composite.scc \
"

COMPATIBLE_MACHINE:pcengines-apux = "pcengines-apux"
