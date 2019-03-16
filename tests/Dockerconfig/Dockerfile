FROM archlinux/base

LABEL author=mynes

RUN pacman -Syu --noconfirm

RUN pacman -Syu make --noconfirm

RUN pacman -Syu cmake --noconfirm

RUN pacman -Syu gcc --noconfirm

RUN pacman -Syu python --noconfirm

RUN pacman -Syu curl --noconfirm

RUN pacman -Syu wget --noconfirm

RUN pacman -Syu tree --noconfirm

RUN pacman -Syu extra/valgrind --noconfirm

RUN pacman -Syu gdb --noconfirm

RUN pacman -Syu file --noconfirm

RUN pacman -Syu python-pip --noconfirm

RUN pip install pyyaml

ADD scripts /scripts

RUN chmod +x /scripts/init.sh

VOLUME /root/42sh

WORKDIR /root/42sh

CMD "/scripts/init.sh"