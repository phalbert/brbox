BRBOX_LIBILCLIENT_VERSION=0.1
BRBOX_LIBILCLIENT_SITE_METHOD=local
BRBOX_LIBILCLIENT_SITE=$(TOPDIR)/../sources/lib/lib-ilclient
BRBOX_LIBILCLIENT_INSTALL_STAGING=YES
BRBOX_LIBILCLIENT_INSTALL_TARGET=YES
$(eval $(cmake-package))

