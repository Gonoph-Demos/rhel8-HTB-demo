FROM	localhost/test:base

RUN	dnf install @postgresql:10 -y \
	&& systemctl enable postgresql \
	&& PGDATA=/var/lib/pgsql/data chroot --userspec=postgres / initdb
