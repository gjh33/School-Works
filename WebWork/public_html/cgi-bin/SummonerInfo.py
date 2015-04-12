import sys

sys.path.append('/home/2015/ljones15/public_html/cgi-bin')

from Riot import Riot
import cgi

def main():
    form = cgi.FieldStorage()
    name = 'gjh33'#form.getvalue("User")
    region = 'na'#form.getvalue("Region")
    doPrint = True #is true if sommoner name successfully returned
    riotDatabase = Riot('11bd2bab-71cc-4445-a06c-152fded0a973')

    print "Content-type: text/html\n\n"

    mainPage = open("SummonerInfo.frm", "rt")
    mainPagePrint = mainPage.read()
    
    try:
        r = riotDatabase.getSummonerByName(name, region)
    except ValueError: #no summoner was returned
        msg = '<font color="red">That summoner does not exist on this server</font>'
        tle = 'Invalid Summoner'
        print mainPagePrint.format(message=msg, title=tle)
        doPrint = False
    else:
        if 'status' in r: #access denied
           if (r['status']['status_code']==401):
                msg = '<font color="red">Server denied access. Try another region</font>'
                tle = 'Server Error'
                print mainPagePrint.format(message=msg, title=tle)
                doPrint = False
    mainPage.close()
    if doPrint:
        print '<html><head><title>Success</title></head><body>'
        print r[name]
        print '</body></html>'


if __name__ == "__main__":
    main()
