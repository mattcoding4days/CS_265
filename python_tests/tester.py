""" A testing script for the grader program """
#!/usr/bin/env python3

# imports
import subprocess as sc
import sys


def clean_output(value: str):
    """ strip newline and anyother trailing garbage """
    clean = value.stdout.decode('utf-8')
    return clean.rstrip()


def main():
    """ Entry point """
    try:
        result = sc.run(['cat', 'test.txt'], capture_output=True, check=True)
    except sc.CalledProcessError:
        print("Command failed")
        sys.exit(1)


    if result.returncode == 0:
        res = clean_output(result)
        print(f"stdout:\n{res}")


if __name__ == '__main__':
    main()
