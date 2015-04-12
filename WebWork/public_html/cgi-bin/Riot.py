#!/usr/bin/python

import requests

class Riot(object):
    region = 'na'
    def __init__(self, api_key, region='na'):
        self.api_key = api_key
        self.region = region
        self.base = 'https://{proxy}.api.pvp.net/api/lol/{region}/{url}'
    def _request(self, api_url, regionI, params={}):
        args = { 'api_key' : self.api_key }
        for key, value in params.items():
            if key not in args:
                args[key] = value
        response = requests.get(
            self.base.format(
                proxy=self.region,
                region=regionI,
                url=api_url
                ),
            params=args
            )
        try:
            toRet = response.json()
        except ValueError:
            raise ValueError
        return toRet
    def getSummonerByName(self, name, regionS=region):
        api_url = 'v1.4/summoner/by-name/{user}'
        api_url = api_url.format(user=name)
        return self._request(api_url, regionS)
