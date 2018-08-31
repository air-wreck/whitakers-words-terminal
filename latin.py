#!/usr/bin/env python2

import sys
import argparse
import readline
import urllib2
import re


# info for connecting to Whitaker's Words server
base = 'http://archives.nd.edu'  # base URL for Whitaker's Words
get = {                          # server resources for translation
    'l': '/cgi-bin/wordz.pl?keyword=',
    'e': '/cgi-bin/wordz.pl?english='
}


# ultimate translation routine
# takes a (term, str), (mode, str), (defs, int); returns results list
def translate(term, mode, defs):
    response = urllib2.urlopen(base + get[mode] + term).read()
    definition = re.findall('<pre>(.*?)</pre>',
                            response.replace('\n', '{newline}'))[0]
    entries = definition.split('{newline}{newline}')
    end = defs + 1
    if defs == 0:
        end = len(entries)
    return [entry.replace('{newline}', '\n') for entry in entries[0:end]]


# main program
def main():
    # default configuration parameters
    defs = 0    # number of entries to show (0 = unlimited)
    mode = 'l'  # default to Latin-to-English


    # if we were given a word as a command-line argument, use that
    parser = argparse.ArgumentParser()
    parser.add_argument('-l', '--latin',   help='latin word to look up')
    parser.add_argument('-e', '--english', help='english word to look up')
    parser.add_argument('-n', '--entries', help='max entries to show (int); ' +
                                                'if blank, show all')
    args = parser.parse_args()
    if args.entries:
        defs = int(args.entries)
    if args.latin:
        print '\n\n'.join(translate(args.latin, 'l', defs)).strip()
        sys.exit(0)
    if args.english:
        print '\n\n'.join(translate(args.english, 'e', defs)).strip()
        sys.exit(0)


    # otherwise, start an interactive session
    try:
        readline.parse_and_bind('tab: complete')
        readline.parse_and_bind('\x1b[A: previous-history')
        readline.parse_and_bind('\x1b[B: next-history')
        print '%s: salve...\n' % sys.argv[0]
        while True:
            text = raw_input('%s %d:> ' % (mode, defs)).strip()

            if text.startswith(':'):  # environment command
                cmd = text[1:]
                if cmd in ['quit', 'q']:
                    break
                elif cmd in ['latin', 'l']:
                    mode = 'l'
                elif cmd in ['english', 'e']:
                    mode = 'e'
                elif cmd.isdigit():
                    defs = int(cmd)

            else:  # word to translate
                print '  ' + '\n\n'.join(translate(text,
                    mode, defs)).strip().replace('\n', '\n  ')

    except (EOFError, KeyboardInterrupt) as e:
        print '%s: received interrupt' % sys.argv[0]

    print '\n%s: vale...'% sys.argv[0]


if __name__ == '__main__':
    main()
