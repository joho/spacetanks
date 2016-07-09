.PHONY: default upload

default:
	platformio run

upload:
	platformio run --target upload
