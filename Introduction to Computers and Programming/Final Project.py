import urllib.request, urllib.parse, urllib.error
import ssl
import re
import requests
from bs4 import BeautifulSoup
from googleapiclient.discovery import build
import wikipedia

#avoid "certificate verify failed"
ssl._create_default_https_context = ssl._create_unverified_context

#make the lists of competitions and dates
competition_list = []
competition_date_list = []

#the name list of men and ladies
men_best_total_score_list = []
ladies_best_total_score_list = []

#get the name list of the season's best score
def nameListOfBestScore(soup):
    names = soup.select("body>div>div>div>div>table[class~=sortable]>tbody>tr>td>a")

    #find those names
    number_of_names = 1
    men_best_total_score_list.clear()
    ladies_best_total_score_list.clear()
    for name in names:
        if number_of_names%3 == 1:
            #men
            if number_of_names<=60:
                men_best_total_score_list.append(name.text)
            #ladies
            elif number_of_names>180 and number_of_names<=240:
                ladies_best_total_score_list.append(name.text)
        number_of_names += 1
    
    #print out the name lists of the season's best score
    print("\nThe top 20 name list of the season's best total score:")
    index = 1
    print("Men:")
    for men in men_best_total_score_list:
        print(index, men)
        index += 1
    index = 1
    print("\nLadies:")
    for ladies in ladies_best_total_score_list:
        print(index, ladies)
        index += 1

#get the date of the competetions
def competetionsAndDate(html):
    competetion_date = re.findall('<td>([A-Z][\D]{,8} [\d]{1,2}[ –]*[A-Z]?[\D ]{,8}\d{0,2})\s?<\/td>',html)
    for date in competetion_date:
        competition_date_list.append(date)

    #get the name of competetions
    competetions = re.findall('<td align=\"center\"><[\S ]*>([\S ]+?)<?\/?a?>?<\/b>',html)
    for competetion in competetions:
        competition_list.append(competetion.lstrip(' &amp;'))

    #make a dictionary of competetions
    print("\nThe dates of the competitions:")
    competition_dict = dict(zip(competition_list, competition_date_list))
    for keys, values in competition_dict.items():
        print(keys, ':', values)
    
    #search in this dictionary
    while True:
        competition_name = input("Enter a name of the competition to know the date, notice the uppercase and lowercase(enter 'EXIT' to stop searching and to see other data):")
        if competition_name.upper() == 'EXIT':
            break
        elif competition_name in competition_dict:
            print(competition_dict[competition_name])
        else:
            print("The competition does not exist.\n")
    
#get the data of this figure skating season by crawling wiki
def crawlingWiki_thisSeason():
    page = urllib.request.urlopen("https://en.wikipedia.org/wiki/2019%E2%80%9320_figure_skating_season")
    html = page.read().decode('utf-8')
    soup = BeautifulSoup(html, 'html.parser')

    print("Following are the datas of 2019–20 figure skating season:")
    nameListOfBestScore(soup)
    competetionsAndDate(html)
    
#get the data of previous figure skating season by crawling wiki
def crawlingWiki_previousSeason(yes_or_no):
    if yes_or_no.upper() == 'Y':
        page = urllib.request.urlopen("https://en.wikipedia.org/wiki/2018%E2%80%9319_figure_skating_season")
        html = page.read().decode('utf-8')
        soup = BeautifulSoup(html, 'html.parser')
        print("Following are the datas of 2018–19 figure skating season:")
        nameListOfBestScore(soup)
    elif yes_or_no.upper() == 'N':
        return
    else:
        print("Wrong input")
        yes_or_no = input("\nDo you want to know more about the previous season?(Y/N)")
        crawlingWiki_previousSeason(yes_or_no)

#use wikipedia API
def wikiAPI(keyword):
    S = requests.Session()

    #make the URL
    URL = "https://en.wikipedia.org/w/api.php"
    PARAMS = {
        "action": "query", #fetch data from wiki
        "format": "json", #output in JSON format
        "list": "search", #get list of pages matching a criteria
        "srsearch": keyword #the page title to search for
    }

    #get the complete URL
    R = S.get(url=URL, params=PARAMS)
    DATA = R.json()

    #output the URL of the searching result on wiki
    pageid = DATA['query']['search'][0]['pageid']
    wiki_url = "https://en.wikipedia.org/?curid=" + str(pageid)
    print("The URL of the searching result on wikipedia is:", wiki_url)

    #avoid "certificate verify failed"
    ssl._create_default_https_context = ssl._create_unverified_context

    #output the first paragraph of the introduction
    print("\nBrief introduction:")
    print(wikipedia.summary(keyword))


DEVELOPER_KEY = 'AIzaSyAzl7Ujixt5VsMuZOXGu2JOMVNW_LszOJo'
YOUTUBE_API_SERVICE_NAME = 'youtube'
YOUTUBE_API_VERSION = 'v3'
COSTUM_SEARCH_API_SERVICE_NAME = 'customsearch'
COSTUM_SEARCH_API_VERSION = 'v1'

#use Youtube API
def youtubeAPI(keyword, number):
    #get API key
    youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION,
    developerKey=DEVELOPER_KEY)
    
    #search Youtube by keyword
    search_response = youtube.search().list(
    q=keyword,
    part='id,snippet',
    maxResults=number, #the number of result
    type="video" #only video, not channel
    ).execute()
    
    #make the lists of video titles and video id
    video_title_list= []
    video_id_list = []

    #deal with the data of Youtube searching
    for search_result in search_response.get('items', []):
        if search_result['id']['kind'] == 'youtube#video':
            #get the video titles and id
            video_title_list.append(search_result['snippet']['title'])
            video_id_list.append(search_result['id']['videoId'])
    #print the searching results
    print("\nSearching results on Youtube:")
    for i in range(number):
        print("Video title:", video_title_list[i])
        print("The URL of the video:", "https://www.youtube.com/watch?v="+video_id_list[i]+'\n')

#use google search API
def googleSearchAPI(keyword, number):
    #get API key
    service = build(COSTUM_SEARCH_API_SERVICE_NAME, COSTUM_SEARCH_API_VERSION,
            developerKey=DEVELOPER_KEY)

    #search by keyword
    res = service.cse().list(
        q=keyword,
        cx='011002983613726928050:3prmsbfrers', #search engine id
        alt='json', #in JSON format
        num=number #the number of result
    ).execute()

    #print the searching results
    print("\nResults of Google Search:")
    for results in res["items"]:
        print("\nWebsite title :", results["htmlTitle"])
        print("Website URL :", results["link"])

#searching the results of the keyword
def searchForOtherResult(keyword):
    #stop searching
    if keyword.upper() == 'EXIT':
        print("Bye!")
        exit()
    else:
        number = int(input("How many results do you want to get?(enter a number)"))
        try:
            wikiAPI(keyword)
            youtubeAPI(keyword, number)
            googleSearchAPI(keyword, number)
        #if the keyword is not good
        except:
            print("Please give another try.(Use a more accurate keyword))")
            keyword = input("Enter something to search(enter 'EXIT' to stop searching):")
            searchForOtherResult(keyword)



if __name__ == '__main__':
    crawlingWiki_thisSeason()
    yes_or_no = input("\nDo you want to know more about the previous season?(Y/N)")
    crawlingWiki_previousSeason(yes_or_no)

    while True:
        #use the data in the lists or enter other things
        what_to_search = input("Enter 'LIST' to use the name lists of men and ladies above, enter 'OTHERS' to search for other things or enter 'EXIT' to quit:")
        #use the data in the lists
        if what_to_search.upper() == 'LIST':
            men_or_ladies = input("Enter 'M' to use the men's name list or enter 'L' to use the ladies' name list:")
            #use the men's name list
            if men_or_ladies.upper() == 'M':
                name_list_index = int(input("Enter the index of the name you want to search for:"))
                #check if the data is in the list
                if name_list_index <=20:
                    keyword = men_best_total_score_list[name_list_index-1]
                    print("Keyword:", keyword)
                    number = int(input("How many results do you want to get?(enter a number)"))
                    wikiAPI(keyword)
                    youtubeAPI(keyword, number)
                    googleSearchAPI(keyword, number)
                else:
                    print("It is not in the list.")
            #use the ladies' name list
            elif men_or_ladies.upper() == 'L':
                name_list_index = int(input("Enter the index of the name you want to search:"))
                #check if the data is in the list
                if name_list_index <=20:
                    keyword = ladies_best_total_score_list[name_list_index-1]
                    print("Keyword:", keyword)
                    number = int(input("How many results do you want to get?(enter a number)"))
                    wikiAPI(keyword)
                    youtubeAPI(keyword, number)
                    googleSearchAPI(keyword, number)
                else:
                    print("It is not in the list.")
            else:
                print("Wrong input")
        #enter other things
        elif what_to_search.upper() == 'OTHERS':
            #enter the keyword you want to search
            keyword = input("Enter something to search(enter 'EXIT' to stop searching):")
            searchForOtherResult(keyword)
        #stop searching
        elif what_to_search.upper() == 'EXIT':
            print("Bye!")
            exit()