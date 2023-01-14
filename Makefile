



PROJECTS = $(filter-out lib, $(notdir $(shell find -maxdepth 1 -type d -name "[!.]*")))
# PROJECTS = $(sort $(notdir $(wildcard *)))

list_projects:
	@echo $(PROJECTS)

.PHONY: $(PROJECTS)

$(PROJECTS):
	$(MAKE) -C $@
