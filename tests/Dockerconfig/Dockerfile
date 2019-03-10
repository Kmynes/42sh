FROM archlinux/base

LABEL author=mynes

RUN pacman -Syu --noconfirm

RUN pacman -Su man --noconfirm

RUN pacman -Su core/man-pages --noconfirm

RUN pacman -Su vim --noconfirm

RUN pacman -Su git --noconfirm

RUN pacman -Su make --noconfirm

RUN pacman -Su cmake --noconfirm

RUN pacman -Su gcc --noconfirm

RUN pacman -Su python --noconfirm

RUN pacman -Su curl --noconfirm

RUN pacman -Su wget --noconfirm

RUN pacman -Su tree --noconfirm

RUN pacman -Su extra/valgrind --noconfirm

RUN pacman -Su gdb --noconfirm

RUN pacman -Su file --noconfirm

ADD edit/.vim /root/.vim

ADD edit/.vimrc /root/.vimrc

ADD scripts /scripts

RUN chmod +x /scripts/init.sh

VOLUME /root/42sh

WORKDIR /root/42sh
