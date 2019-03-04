# RHEL 8 HTB Demo
This set of demo and ansible scripts:

1. Creates a set of VMs (demo[1:3])
2. Configures them for Ansible
3. Installs the scripts and container build files

## Demo steps

1. Demo1: Show cockpit
    * https://demo1.virt.gonoph.net:9090/
2. Demo1: Show composer
    * https://demo1.virt.gonoph.net:9090/
3. Demo1: Show appstream and baseos
    * ```bash
      dnf module list mysql
      dnf module install mysql:8.0/client
      dnf module install mysql:8.0/server
      dnf module list postgresql
      version=9 # version=10
      dnf module install postgresql:$version/$profile
      ```
4. Demo2: Show postgres9 and postgres10
5. Demo3: Show container version of postgres9 and postgres10
    * ```bash
       cd ~/demo-container && make
       tmux
       podman run --rm -it --name v10 localhost/test:10 # session 1
       podman run --rm -it --name v9 localhost/test:9   # session 2
       podman exec -it v10 ps auxw                      # session 3
       podman exec -it v9 ps auxw                       # session 3
       ```
6. Demo3: Show podman, skopeo, buildah difference to docker
7. Demo1: Show openssl tighened security with FIPS
    * ```bash
      ssl_test server                                   # session 1
      ssl_test client                                   # session 2
      ```
8. Demo1: Show VDO example
9. Demo1: Show eBPF
    * tcptop
    * sslsnoop
    * oomkiler
    * `/usr/share/bcc/tools/oomkill`
