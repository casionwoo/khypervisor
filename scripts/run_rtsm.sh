#!/bin/sh
RTSM_VE_Cortex-A15x1-A7x1 -C motherboard.smsc_91c111.enabled=1 -C motherboard.hostbridge.userNetworking=1 -a coretile.cluster0.cpu0=platform-device/cortex_a15x2_rtsm/hvc-man-switch.axf
