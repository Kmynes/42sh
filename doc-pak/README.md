# 42sh
BlueShell42's 42sh project


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
docker-compose run 42sh_arch make check
```