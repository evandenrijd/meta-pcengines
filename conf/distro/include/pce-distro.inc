DISTRO = "pce"
DISTRO_NAME = "pce"
SDK_VENDOR = "-pcesdk"
TARGET_VENDOR = "-pce"

DISTRO_VERSION = "0.1"
DISTRO_CODENAME = "sumo"
SDK_VERSION := "${@'${DISTRO_VERSION}'.replace('snapshot-${DATE}','snapshot')}"

MAINTAINER = "pcengines"

LOCALCONF_VERSION = "1"

DISTRO_VERSION[vardepsexclude] = "DATE"
SDK_VERSION[vardepsexclude] = "DATE"

PCENGINES_DEFAULT_DISTRO_FEATURES = " \
    largefile \
    ptest \
    multiarch \
    systemd \
    pci \
    usbgadget \
    usbhost \
    keyboard \
    nfs \
    "
PCENGINES_DEFAULT_EXTRA_RDEPENDS = "packagegroup-core-boot"
PCENGINES_DEFAULT_EXTRA_RRECOMMENDS = "kernel-module-af-packet"

DISTRO_FEATURES ?= " \
    ${DISTRO_FEATURES_DEFAULT} \
    ${DISTRO_FEATURES_LIBC} \
    ${PCENGINES_DEFAULT_DISTRO_FEATURES} \
    ${PCENGINES_EXTRA_DISTRO_FEATURES} \
    "

DISTRO_FEATURES_remove = " opengl wayland x11 vulkan alsa pulseaudio"

PREFERRED_VERSION_linux-yocto ?= "4.14%"

SDK_NAME = "${DISTRO}-${TCLIBC}-${SDK_ARCH}-${IMAGE_BASENAME}-${TUNE_PKGARCH}"
SDKPATH = "/opt/${DISTRO}/${SDK_VERSION}"

DISTRO_EXTRA_RDEPENDS += " ${PCENGINES_DEFAULT_EXTRA_RDEPENDS}"
DISTRO_EXTRA_RRECOMMENDS += " ${PCENGINES_DEFAULT_EXTRA_RRECOMMENDS}"

POKYQEMUDEPS = "${@bb.utils.contains("INCOMPATIBLE_LICENSE", "GPL-3.0", "", "packagegroup-core-device-devel",d)}"
DISTRO_EXTRA_RDEPENDS_append_qemux86-64 = " ${POKYQEMUDEPS}"

TCLIBCAPPEND = ""

QEMU_TARGETS ?= "x86_64"

PREMIRRORS ??= "\
bzr://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
cvs://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
git://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
gitsm://.*/.* http://downloads.yoctoproject.org/mirror/sources/ \n \
hg://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n \
osc://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
p4://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n \
svn://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n"

MIRRORS =+ "\
ftp://.*/.*      http://downloads.yoctoproject.org/mirror/sources/ \n \
http://.*/.*     http://downloads.yoctoproject.org/mirror/sources/ \n \
https://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n"

# The CONNECTIVITY_CHECK_URI's are used to test whether we can succesfully
# fetch from the network (and warn you if not). To disable the test set
# the variable to be empty.
# Git example url: git://git.yoctoproject.org/yocto-firewall-test;protocol=git;rev=master
CONNECTIVITY_CHECK_URIS ?= "https://www.example.com/"

SANITY_TESTED_DISTROS ?= " \
            poky-2.4 \n \
            poky-2.5 \n \
            ubuntu-15.04 \n \
            ubuntu-16.04 \n \
            ubuntu-16.10 \n \
            ubuntu-17.04 \n \
            fedora-26 \n \
            centos-7 \n \
            debian-8 \n \
            debian-9 \n \
            opensuse-42.1 \n \
            opensuse-42.2 \n \
            "
#
# OELAYOUT_ABI allows us to notify users when the format of TMPDIR changes in
# an incompatible way. Such changes should usually be detailed in the commit
# that breaks the format and have been previously discussed on the mailing list
# with general agreement from the core team.
#
OELAYOUT_ABI = "12"

# add poky sanity bbclass
INHERIT += "poky-sanity"

# QA check settings - a little stricter than the OE-Core defaults
WARN_TO_ERROR_QA = "already-stripped compile-host-path install-host-path \
                    installed-vs-shipped ldflags pn-overrides rpaths staticdev \
                    unknown-configure-option useless-rpaths"
WARN_QA_remove = "${WARN_TO_ERROR_QA}"
ERROR_QA_append = " ${WARN_TO_ERROR_QA}"

require conf/distro/include/poky-world-exclude.inc
require conf/distro/include/no-static-libs.inc
require conf/distro/include/yocto-uninative.inc
require conf/distro/include/security_flags.inc
INHERIT += "uninative"