#!/usr/bin/python

import string, locale, sys
from optparse import OptionParser

locale.setlocale(locale.LC_COLLATE, 'C')

class comm:
    
    # open file upon creating a comm object
    # read file, place in self.text
    # close file

    def __init__( self, filename ):
        f = open( filename, 'r' )
        self.text = f.read()
        f.close()

    # function returns a list of each word
    # from self.text using split()
    # function from import string

    def getList(self):
        return self.text.split()

def main():
    version_msg = "hannah chung's %prog"
    usage_msg = """%prog [-123] FILE1 FILE2

the comm utility shall read FILE1 and FILE2, which should be ordered in the current collating sequence, and produce three text columns as output: lines only in FILE1, lines only in FILE2, and lines in both files.
"""
    parser = OptionParser(version=version_msg, usage=usage_msg)

    parser.add_option( "-1", action="store_true", dest="suppress1", default=False, help="suppress the output column of lines unique to FILE1." )
    parser.add_option( "-2", action="store_true", dest="suppress2", default=False, help="supress the output column of lines unique to FILE2." )
    parser.add_option( "-3",  action="store_true", dest="suppress3", default=False, help="suppress the output column of lines duplicated in FILE1 and FILE2." )
    parser.add_option( "-u", action="store_true", dest="unsorted", default=False, help="used if files are not already sorted. output items will appear in the same order as input lines, or in order of first appearrance if duplicate." )

    (options, args) = parser.parse_args(sys.argv[1:])
    
    wordlist1 = list()
    wordlist2 = list()
    wordlist3 = list()
    mergedlist = list()

    # extract arguments and determine whether reading from filename
    # or reading from standard input;
    # create list of words from file text and place in wordlist1 and wordlist2 

    if len(args) != 2:
        parser.error("incorrect number of arguments. must compare at least two files, or one file and another from stdin." )

    elif args[0] == "-":
        inputfile1 = sys.stdin.read()
        wordlist1 = inputfile1.split()

        wordlist2  = comm(args[1]).getList()

    elif args[1] == "-":
        inputfile2 = sys.stdin.read()
        wordlist2 = inputfile2.split()

        wordlist1  = comm(args[0]).getList()
        
    else:
        wordlist1 = comm(args[0]).getList()
        wordlist2 = comm(args[1]).getList()

    # merge lists and remove duplicates

    mergedlist = list(wordlist1 + wordlist2)
    
    if options.unsorted == False:
        mergedlist.sort()
        
    if options.suppress1 == True:
        if options.suppress2 == False:
            for i in range(len(mergedlist)):
                if mergedlist[i] in wordlist2 and mergedlist[i] not in wordlist1:
                    wordlist3.append(mergedlist[i])
                    wordlist2.remove(mergedlist[i])
                if options.suppress3 == False:
                    if mergedlist[i] in wordlist2 and mergedlist[i] in wordlist1:
                        wordlist3.append('\t' + mergedlist[i])
                        wordlist1.remove(mergedlist[i])
                        wordlist2.remove(mergedlist[i])
        else:
            if options.suppress3 == False:
                for i in range(len(mergedlist)):
                    if mergedlist[i] in wordlist2 and mergedlist[i] in wordlist1:
                        wordlist3.append(mergedlist[i])
                        wordlist1.remove(mergedlist[i])
                        wordlist2.remove(mergedlist[i])

    elif options.suppress2 == True:
        if options.suppress1 == False:
            for i in range(len(mergedlist)):
                if mergedlist[i] in wordlist1 and mergedlist[i] not in wordlist2:
                    wordlist3.append(mergedlist[i])
                    wordlist1.remove(mergedlist[i])
                if options.suppress3 == False:
                    if mergedlist[i] in wordlist1 and mergedlist[i] in wordlist2:
                        wordlist3.append('\t' + mergedlist[i])
                        wordlist1.remove(mergedlist[i])
                        wordlist2.remove(mergedlist[i])
        else:
            if options.suppress3 == False:
                for i in range(len(mergedlist)):    
                    if mergedlist[i] in wordlist1 and mergedlist[i] in wordlist2:
                        wordlist3.append(mergedlist[i])
                        wordlist1.remove(mergedlist[i])
                        wordlist2.remove(mergedlist[i])

    elif options.suppress3 == True:
        if options.suppress1 == False:
            for i in range(len(mergedlist)):
                if mergedlist[i] in wordlist1 and mergedlist[i] not in wordlist2:
                    wordlist3.append(mergedlist[i])
                    wordlist1.remove(mergedlist[i])
                if options.suppress2 == False:
                    if mergedlist[i] in wordlist2 and mergedlist[i] not in wordlist1:
                        wordlist3.append('\t' + mergedlist[i])
                        wordlist2.remove(mergedlist[i])
        else:
            if options.suppress2 == False:
                for i in range(len(mergedlist)):
                    if mergedlist[i] in wordlist2 and mergedlist[i] not in wordlist1:
                        wordlist3.append(mergedlist[i])
                        wordlist2.remove(mergedlist[i])

    else:
        for i in range(len(mergedlist)):
            if mergedlist[i] in wordlist1 and mergedlist[i] not in wordlist2:
                wordlist3.append(mergedlist[i])
                wordlist1.remove(mergedlist[i])
            elif mergedlist[i] in wordlist2 and mergedlist[i] not in wordlist1:
                wordlist3.append('\t' + mergedlist[i])
                wordlist2.remove(mergedlist[i])
            elif mergedlist[i] in wordlist1 and mergedlist[i] in wordlist2:
                wordlist3.append('\t\t' + mergedlist[i])
                wordlist1.remove(mergedlist[i])
                wordlist2.remove(mergedlist[i])

    if options.suppress1 == True and options.suppress2 == True and options.suppress3 == True:
        return None
                
    print('\n'.join(wordlist3))
        
if __name__=='__main__':
    main()
