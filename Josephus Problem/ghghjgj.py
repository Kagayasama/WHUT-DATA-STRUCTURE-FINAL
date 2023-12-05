import requests
from bs4 import BeautifulSoup
import bs4
def getHTMLText(url):
    try:
        r = requests.get(url, timeout=30)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return ""

def fillUnivLIst(ulist, html):
    soup = bs4.BeautifulSoup(html, "html.parser")
    for tr in soup.find('tbody').children:
        #检测tag类型，过滤非tag类型标签
        if isinstance(tr, bs4.element.Tag):
            tds = tr('td')
            ulist.append([str(tr('td')[0].contents[0]).strip(), tds[1].a.string, str(tr('td')[4].contents[0]).strip()])
    return ulist

def printUnivList(ulist, num):
    #tplt = "{0:^10}\t{1:{3}^6}\t{2:^10}"
    print("{:^10}\t{:^6}\t{:^10}".format("排名","学校名称","总分"))
    #     print(tplt.format("排名","学校名称","总分",chr=(12288)))
    for i in range(num):
        u=ulist[i]
        print("{:^10}\t{:^6}\t{:^10}".format(u[0],u[1],u[2]))
#         print(tplt.format(u[0],u[1],u[2],chr=(12288)))

def main():
    ulist = []
    url = 'https://www.shanghairanking.cn/rankings/bcur/2020'
    html = getHTMLText(url)
    ulist = fillUnivLIst(ulist, html)
    printUnivList(ulist, 20)


main()