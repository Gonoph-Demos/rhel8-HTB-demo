.PHONY: all base p9 p10

FLAGb  := .flag-base
FLAG10 := .flag-postgres10
FLAG9  := .flag-postgres9

PODMAN := sudo podman
MNT    := /tmp/builder
MOUNTS := -v /tmp/builder:/var/cache:z

all: p9 p10

p9: $(FLAG9)

p10: $(FLAG10)

base: $(FLAGb)

$(MNT):
	mkdir -p $(MNT)

$(FLAG10): base postgres-10.dockerfile Makefile $(MNT)
	$(PODMAN) build $(MOUNTS) -f postgres-10.dockerfile -t localhost/test:10 .

$(FLAG9): base postgres-9.dockerfile Makefile $(MNT)
	$(PODMAN) build $(MOUNTS) -f postgres-9.dockerfile -t localhost/test:9 .

$(FLAGb): base.dockerfile Makefile $(MNT)
	$(PODMAN) build $(MOUNTS) -f base.dockerfile -t localhost/test:base .
