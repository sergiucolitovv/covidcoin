Sample init scripts and service configuration for covid19d
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/covid19d.service:    systemd service unit configuration
    contrib/init/covid19d.openrc:     OpenRC compatible SysV style init script
    contrib/init/covid19d.openrcconf: OpenRC conf.d file
    contrib/init/covid19d.conf:       Upstart service configuration file
    contrib/init/covid19d.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "covid19" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes covid19d will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, covid19d requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, covid19d will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that covid19d and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If covid19d is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running covid19d without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/covid19.conf.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/covid19d
Configuration file:  /etc/covid19/covid19.conf
Data directory:      /var/lib/covid19d
PID file:            `/var/run/covid19d/covid19d.pid` (OpenRC and Upstart) or `/run/covid19d/covid19d.pid` (systemd)
Lock file:           `/var/lock/subsys/covid19d` (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the covid19 user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
covid19 user and group.  Access to covid19-cli and other covid19d rpc clients
can then be controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the covid19 group
access to files under it _if_ the files themselves give permission to the
covid19 group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/covid19/covid19.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/covid19/covid19.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `BITCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/covid19d`
Configuration file:  `~/Library/Application Support/COVID19/covid19.conf`
Data directory:      `~/Library/Application Support/COVID19`
Lock file:           `~/Library/Application Support/COVID19/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start covid19d` and to enable for system startup run
`systemctl enable covid19d`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename covid19d.openrc to covid19d and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/covid19d start` and configure it to run on startup with
`rc-update add covid19d`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop covid19d.conf in /etc/init.  Test by running `service covid19d start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy covid19d.init to /etc/init.d/covid19d. Test by running `service covid19d start`.

Using this script, you can adjust the path and flags to the covid19d program by
setting the COVID19D and FLAGS environment variables in the file
/etc/sysconfig/covid19d. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.covid19.covid19d.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.covid19.covid19d.plist`.

This Launch Agent will cause covid19d to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run covid19d as the current user.
You will need to modify org.covid19.covid19d.plist if you intend to use it as a
Launch Daemon with a dedicated covid19 user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
