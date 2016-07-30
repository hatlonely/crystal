#!/usr/bin/env python3

import httplib2
import json
import re

http = httplib2.Http(".cache")

class HearthStoneCards(object):
    def __init__(self):
        hearthstone_api = 'https://omgvamp-hearthstone-v1.p.mashape.com/cards'
        headers = {
            "X-Mashape-Key": "pV0H4sgXuWmshSg72QHQGlmKDYQ9p1r2hWwjsnPcpQ0K6U77ue"
        }
        response, content = http.request(hearthstone_api, 'GET', headers=headers)
        self.cards = json.loads(content.decode('utf-8'))
        # self.cards = json.load(open('hearthstone.json', encoding='utf-8'))


    def download(self, card):
        filename = '{0}_{1}'.format(re.compile(r'[\W]').sub('_', card['name']), card['cardId']).lower()
        if "img" in card:
            print('{0}\t{1}'.format(card['name'], card["img"]))
            response, content = http.request(card['img'], 'GET')
            fp = open('cards/{0}.png'.format(filename), 'wb')
            fp.write(content)
            fp.close()
        if "imgGold" in card:
            print('{0}\t{1}'.format(card['name'], card["imgGold"]))
            response, content = http.request(card['imgGold'], 'GET')
            fp = open('card_golds/{0}.gif'.format(filename), 'wb')
            fp.write(content)
            fp.close()


    def process(self):
        index = 0
        for key in self.cards:
            for card in self.cards[key]:
                index += 1
                print(index)
                self.download(card)


def main():
    heartstone_cards = HearthStoneCards()
    heartstone_cards.process()


if __name__ == '__main__':
    main()
