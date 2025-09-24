PDF_NAME := doc.pdf
UNAME 		:= $(strip $(OS))

# Checking whether folder exists or not is different between mac/linux and windows
ifeq ($(UNAME),Windows_NT)
$(info I am sorry for using Windows)
DELETE		:= rmdir /S /Q
GENERATE_PDF = cd latex && make.bat && copy /Y refman.pdf ..\$(PDF_NAME) >NUL
else 
$(info I can't update my mac but I love it so much)
DELETE		:= rm -f
GENERATE_PDF = $(MAKE) -C latex && cp latex/refman.pdf $(PDF_NAME)
endif 

create_doxy: 
	doxygen Doxyfile

create_pdf: 
	$(GENERATE_PDF)

clean: 
	-$(DELETE) latex 
	-$(DELETE) html 


all: create_doxy create_pdf clean
