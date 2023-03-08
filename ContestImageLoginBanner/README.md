This page was helpful:
https://help.gnome.org/admin/system-admin-guide/stable/login-banner.html.en
But in a nutshell:

Network address changes service
/etc/systemd/system/icpc_updatebanner.service
Executes /home/pc2/update-banner shell script
Runs every 30 seconds
Enumerates all network interfaces
If network changes, updates /etc/dconf/db/gdm.d/01-banner-message

[org/gnome/login-screen]
banner-message-enable=true
banner-message-text='message text\ngoes here\nline3.

The banner messages are displayed on the login screen as lines of text.
https://photos.app.goo.gl/PVyZGaFdcxcZy63f7

Needed to create /etc/dconf/profile/gdm:
user-db:user
system-db:gdm
file-db:/usr/share/gdm/greeter-dconf-defaults

Create gdm keyfile /etc/dconf/db/gdm.d/01-banner-message as above

Update the db database:  dconf update

systemctl enable icpc_updatebanner.service

Sends to pc2server using port 80 and netcat (nc) with 5 second timeout (port 80 is probably a bad choice)
script on pc2server (/root/sh.watchnet) processes the input by adding icpc_watchnet.service (not included here,
but available if wanted)

