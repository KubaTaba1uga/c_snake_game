#!/bin/bash
OS=$(hostnamectl | grep "Operating System")


case "$OS" in
    *"Debian GNU/Linux"*)
	sudo apt update
	sudo apt-get install libczmq-dev -y

	;;
    *)
	echo "OS not supported"
	exit 1
	;;
    esac
