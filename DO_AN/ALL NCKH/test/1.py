#!/usr/bin/env python
# encoding: utf-8
import os, sys, requests
import json, re, time
from retrying import retry
from contextlib import closing


class DouYin:
    def __init__(self):
        self.headers = {
            'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
            'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8',
            'pragma': 'no-cache',
            'cache-control': 'no-cache',
            'upgrade-insecure-requests': '1',
            'User-Agent': 'Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1',
        }
    def get_video_urls(self, sec_uid, type_flag='p'):
        '''
        获取用户的视频链接
        type_flag：视频类型
        返回：昵称，video_list
        '''
        user_url_prefix = 'https://www.iesdouyin.com/web/api/v2/aweme/post' if type_flag == 'p' else 'https://www.iesdouyin.com/web/api/v2/aweme/like'
        print('---解析视频链接中...\r')

        i = 0
        result = []
        while result == []:
            i = i + 1
            print('---正在第 {} 次尝试...\r'.format(str(i)))
            user_url = user_url_prefix + '/?sec_uid=%s&count=2000' % (sec_uid)
            response = self.get_request(user_url)
            html = json.loads(response.content.decode())
            if html['aweme_list'] != []:
                result = html['aweme_list']

        nickname = None
        count=0
        video_list = []
        for item in result:
            count+=1
            if nickname is None:
                nickname = item['author']['nickname'] if re.sub(r'[\/:*?"<>|]', '',
                                                                item['author']['nickname']) else None

            video_list.append({
                'desc': "{}.".format(str(count))+re.sub(r'[\/:*?"<>|\n]', '', item['desc']) if item['desc'] else "{}.".format(str(count))+'无标题' + str(int(time.time())),
                'url': item['video']['play_addr']['url_list'][0]
            })
        return nickname, video_list

    def get_download_url(self, video_url, watermark_flag):
        
        if watermark_flag == True:
            download_url = video_url.replace('api.amemv.com', 'aweme.snssdk.com')
        else:
            download_url = video_url.replace('aweme.snssdk.com', 'api.amemv.com')

        return download_url

    def hello(self):
        print("开始解析")
        return self

    def run(self):
        sec_uid = 'MS4wLjABAAAAuc2-ZhGi1vmVQl-K6IcTm2Rxvk5UG6BEkSbywa-MVMQ'
        watermark_flag = 0
        watermark_flag = bool(int(watermark_flag)) if watermark_flag else 0
         #这里参数f是下载喜欢，p是下载作品     
        type_flag ='f' 
        
         #下载目录
        save_dir = "./Download/"
    
        nickname, video_list = self.get_video_urls(sec_uid, type_flag)
        nickname_dir = os.path.join(save_dir, nickname)

        if not os.path.exists(nickname_dir):
            os.makedirs(nickname_dir)

        if type_flag == 'f':
            if 'favorite' not in os.listdir(nickname_dir):
                os.mkdir(os.path.join(nickname_dir, 'favorite'))

        print('---视频下载中: 共有%d个作品...\r' % len(video_list))
        sum1 = int(input('需要下载几个：'))
        for num in range(sum1):
            print('---正在解析第%d个视频链接 [%s] 中，请稍后...\n' % (num + 1, video_list[num]['desc']))

            video_path = os.path.join(nickname_dir, video_list[num]['desc']) if type_flag != 'f' else os.path.join(
                nickname_dir, 'favorite', video_list[num]['desc'])
            if os.path.isfile(video_path):
                print('---视频已存在...\r')
            else:
                self.video_downloader(video_list[num]['url'], video_path, watermark_flag)
            print('\n')
        print('---下载完成...\r')
    def video_downloader(self, video_url, video_name, watermark_flag=False):
        '''
        下载视频
         video_url：视频的网址
         video_name：视频的名称
         watermark_flag：视频的标志
        返回：无    
            '''
        size = 0
        video_url = self.get_download_url(video_url, watermark_flag=watermark_flag)
        with closing(requests.get(video_url, headers=self.headers, stream=True)) as response:
            chunk_size = 1024
            content_size = int(response.headers['content-length'])
            if response.status_code == 200:
                sys.stdout.write('----[文件大小]:%0.2f MB\n' % (content_size / chunk_size / 1024))

                with open(video_name + '.mp4', 'wb') as file:
                    for data in response.iter_content(chunk_size=chunk_size):
                        file.write(data)
                        size += len(data)
                        file.flush()

                        sys.stdout.write('----[下载进度]:%.2f%%' % float(size / content_size * 100) + '\r')
                        sys.stdout.flush()

    @retry(stop_max_attempt_number=3)
    def get_request(self, url, params=None):
        
        if params is None:
            params = {}
        response = requests.get(url, params=params, headers=self.headers, timeout=10)
        assert response.status_code == 200
        return response

    @retry(stop_max_attempt_number=3)
    def post_request(self, url, data=None):
        if data is None:
            data = {}
        response = requests.post(url, data=data, headers=self.headers, timeout=10)
        assert response.status_code == 200
        return response

    def run(self):
        sec_uid = 'MS4wLjABAAAAuc2-ZhGi1vmVQl-K6IcTm2Rxvk5UG6BEkSbywa-MVMQ'
        watermark_flag = 0
        watermark_flag = bool(int(watermark_flag)) if watermark_flag else 0
         #这里参数f是下载喜欢，p是下载作品     
        type_flag ='f' 
        
         #下载目录
        save_dir = "./Download/"
    
        nickname, video_list = self.get_video_urls(sec_uid, type_flag)
        nickname_dir = os.path.join(save_dir, nickname)

        if not os.path.exists(nickname_dir):
            os.makedirs(nickname_dir)

        if type_flag == 'f':
            if 'favorite' not in os.listdir(nickname_dir):
                os.mkdir(os.path.join(nickname_dir, 'favorite'))

        print('---视频下载中: 共有%d个作品...\r' % len(video_list))
        sum1 = int(input('需要下载几个：'))
        for num in range(sum1):
            print('---正在解析第%d个视频链接 [%s] 中，请稍后...\n' % (num + 1, video_list[num]['desc']))

            video_path = os.path.join(nickname_dir, video_list[num]['desc']) if type_flag != 'f' else os.path.join(
                nickname_dir, 'favorite', video_list[num]['desc'])
            if os.path.isfile(video_path):
                print('---视频已存在...\r')
            else:
                self.video_downloader(video_list[num]['url'], video_path, watermark_flag)
            print('\n')
        print('---下载完成...\r')


if __name__ == "__main__":
    DouYin().hello().run()

