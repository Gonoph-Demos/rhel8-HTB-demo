FROM	registry.redhat.io/ubi8/ubi:latest

MAINTAINER	Billy Holmes <biholmes@redhat.com>

ENV	B='\[\033[01;30m\]'
ENV	G='\[\033[01;32m\]'
ENV	n='\[\033[0m\]'
ENV	b='\[\033[01;34m\]'

ENV	PS1="$B(${G}container$B)$n [\u@\h $b\W$n]\$ " \
	LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8 LC_CTYPE=en_US.UTF-8


RUN	cd /etc/yum.repos.d \
	&& dnf repolist --disablerepo='*' \
	&& sed -i 's/enabled *= *1/enabled = 0/' .repo \
	&& dnf repolist \
		--enablerepo='rhel-8-for-x86_64-appstream-rpms' \
		--enablerepo='rhel-8-for-x86_64-baseos-rpms' \
	&& dnf update -y && false || true \
	&& dnf install -y procps-ng glibc-langpack-en.x86_64
