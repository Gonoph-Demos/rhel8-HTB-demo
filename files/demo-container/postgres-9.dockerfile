FROM	localhost/test:base

RUN	dnf install @postgresql:9.6 -y \
	&& systemctl enable postgresql \
	&& PGDATA=/var/lib/pgsql/data chroot --userspec=postgres / initdb
