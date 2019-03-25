# 42sh
BlueShell42's 42sh project

## Install
For test this project you need the following programme installed:
* ``Docker``
* ``make``

### Docker
If you are on ``Windows`` you can install it by download the following executable file : [docker.exe](https://download.docker.com/win/stable/Docker%20for%20Windows%20Installer.exe)

If you are on ``Ubuntu`` you just have to run the following commands:

#### Install docker repository
```sudo apt-get update```

```sudo apt-get install apt-transport-https ca-certificates curl gnupg-agent software-properties-common```

```curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -```

```sudo apt-key fingerprint 0EBFCD88```

```sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"```

#### Install docker
```sudo apt-get update```

```sudo apt-get install docker-ce docker-ce-cli containerd.io```

### make
If you are on windows maybe you don't have make installed.

So you can install the ``choco`` package manager by running the following command as administrator in a Powershell:

```Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))```

Then you can install ``make`` by running the following command

```choco install make```
After that set the directory of ``make.exe`` in your environment variable ``path`` and you will be allowed to run ``make``

When ``docker`` and ``make`` are installed ou just have to open a terminal in the project root and run the command ```make check```. Then the project will be compiled and tested.

## Dev
You should "make check" before every commit to check no bug have been introduced

To enforce this, we use a pre-commit hook (see https://git-scm
.com/book/en/v2/Customizing-Git-Git-Hooks)

To install it just run
```bash
ln -s ../../pre-commit.sh .git/hooks/pre-commit
```

### Docker testing

You can run test in an environement with docker by running

```
docker-compose run 42sh_arch
```

### Makefile

We are using ``make`` for compile our project.

This is the targets:
* ```make all``` or just ```make``` just generate the project
* ```make test``` Build the project and run the test for each functions
* ```make check``` Create an environement with ``Docker`` for reproduced the environment of ``archlinux`` and execute ```make test``` inside it
