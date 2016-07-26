#!/usr/bin/env python3

import httplib2
import pyquery

http = httplib2.Http(".cache")
headers = {
    "User-Agent":"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36",
    "Accept-Language": "zh-CN"
}


class DoubanMovieTop250(object):
    def __init__(self):
        self.urls = []
        for i in range(0, 10):
            self.urls.append('https://movie.douban.com/top250?start={0}&filter='.format(i * 25))
        self.content = []
        self.movies = []

    def analysis(self, url):
        response, content = http.request(url, 'GET', headers=headers)
        jquery = pyquery.PyQuery(content)
        count = 1
        for movie_info in jquery('div.item').items(''):
            movie = {'chinese_name': '', 'english_name': ''}
            movie['href'] = movie_info('div.hd a').attr('href')
            count = 0
            for title in movie_info('div.hd').items('.title'):
                if count == 0:
                    movie['chinese_name'] = title.text()
                if count == 1:
                    movie['english_name'] = title.text().strip(' /\xa0')
                count += 1
            movie['other'] = movie_info('.other').text().strip(' /\xa0')
            movie['star'] = movie_info('div.bd')('.rating_num').text()
            movie['quote'] = movie_info('div.bd')('.inq').text()
            self.movies.append(movie)

    def process(self):
        for url in self.urls:
            self.analysis(url)

    def result(self):
        return self.movies


def main():
    doubanMovieTop250 = DoubanMovieTop250()
    doubanMovieTop250.process()
    index = 0
    for movie in doubanMovieTop250.result():
        index += 1
        print('{index}\t{0[star]}\t{0[chinese_name]}\t{0[quote]}\t{0[href]}'.format(movie, index=index))


if __name__ == '__main__':
    main()
