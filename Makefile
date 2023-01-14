



PROJECTS = $(filter-out lib, $(notdir $(shell find -maxdepth 1 -type d -name "[!.]*")))
# PROJECTS = $(sort $(notdir $(wildcard *)))

.PHONY: $(PROJECTS)

all:
	for i in $(PROJECTS); do $(MAKE) -C $$i || exit 1; done

$(PROJECTS):
	$(MAKE) -C $@


distclean:
	for i in $(PROJECTS); do $(MAKE) -C $$i clean || exit 1; done
