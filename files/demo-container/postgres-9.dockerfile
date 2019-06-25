FROM	localhost/test:base

RUN	dnf install @postgresql:9.6 -y \
	&& systemctl enable postgresql \
	&& PGDATA=/var/lib/pgsql/data chroot --userspec=postgres / initdb

RUN	echo "host all  all    0.0.0.0/0  md5" >> /var/lib/pgsql/data/pg_hba.conf \
	&& echo "listen_addresses='*'" >> /var/lib/pgsql/data/postgresql.conf

USER	postgres
EXPOSE	5432
ENV	PGDATA=/var/lib/pgsql/data
CMD [ "/usr/bin/postmaster", "-D", "/var/lib/pgsql/data", "-r", "-" ]
