Demo steps:

1. Demo1: Show cockpit
    https://demo1.virt.gonoph.net:9090/
2. Demo1: Show composer
    https://demo1.virt.gonoph.net:9090/
3. Demo1: Show appstream and baseos
    dnf module list mysql
    dnf module install mysql:8.0/client
    dnf module install mysql:8.0/server
    dnf module list postgresql
    dnf module install postgresql:$version/$profile
4. Demo2: Show postgres9 and postgres10
5. Demo3: Show container version of postgres9 and postgres10
    cd ~/demo-container && make
    tmux
      1: podman run --rm -it --name v10 localhost/test:10
      2: podman run --rm -it --name v9 localhost/test:9
      3: podman exec -it v10 ps auxw
      3: podman exec -it v9 ps auxw
6. Demo3: Show podman, skopeo, buildah difference to docker
7. Demo1: Show openssl tighened security with FIPS
      1: ssl_test server
      2: ssl_test client
8. Demo1: Show VDO example
9. Demo1: Show eBPF - tcptop, sslsnoop, oomkiler: /usr/share/bcc/tools/oomkill
