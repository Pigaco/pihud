#!/bin/bash

/opt/chroots/debian_jessie_x32/mount_jenkins.sh


echo "Build Pihud"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "mkdir -p /root/jenkins/workspace/pihud_x32/build"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "rm -f /root/jenkins/workspace/pihud_x32/build/piga-libpihud*"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/pihud_x32/build && cmake .. -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake -DPIHUD_VERSION_PATCH="\""$(cat /var/lib/jenkins/jobs/pihud_x32/nextBuildNumber)"\"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/pihud_x32/build && make"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/pihud_x32/build && make package"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/pihud_x32/build && make install"

echo "Add the package to the repository"
PIGA_DEB="$(ls /var/lib/jenkins/workspace/pihud_x32/build/*deb)"
echo "DEBFILE: $PIGA_DEB"
cd /media/maximaximal.com/www/repos/apt/debian && sudo reprepro includedeb jessie "$PIGA_DEB"

/opt/chroots/debian_jessie_x32/umount_jenkins.sh
