#!/bin/sh

set -x 
ansible-playbook  -i inventory --vault-password-file=vault.txt create.yml "$@"
