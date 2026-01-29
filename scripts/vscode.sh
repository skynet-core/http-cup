#!/bin/sh

os="$(uname -s | tr '[:upper:]' '[:lower:]')"

cd .devcontainer || exit 1

if [ -n "$DEV_CONTAINER" ] || [ -n "$container" ] || [ -n "$REMOTE_CONTAINERS" ]; then
	echo "error: this script must run from host" 1>&2
	exit 1
fi

if [ ! "$os" = "linux" ]; then
	ln -sf devcontainer.podman.json devcontainer.json
else
	if which docker 1>/dev/null 2>&1; then
		ln -sf devcontainer.docker.json devcontainer.json
	else
		ln -sf devcontainer.podman.json devcontainer.json
	fi
fi

# ./setup.sh "$(realpath ../)"
