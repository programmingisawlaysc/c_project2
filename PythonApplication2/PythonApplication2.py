import pyautogui
from selenium import webdriver
from time import sleep
from PIL import Image
import pytesseract
import chromedriver_autoinstaller
import pymysql

def image_crop( infilename , save_path):
 
    img = Image.open( infilename )
    (img_h, img_w) = img.size
    print(img.size)
 
    # crop 할 사이즈 : grid_w, grid_h
    grid_w = 52.5555555556 # crop width
    grid_h = 52.5555555556 # crop height
    range_w = (int)(img_w/grid_w)
    range_h = (int)(img_h/grid_h)
    print(range_w, range_h)
 
    i = 0
    croping_area = (7,7,48,48)
    for w in range(range_w+1):
        for h in range(range_h+1):
            bbox = (h*grid_h, w*grid_w, (h+1)*(grid_h), (w+1)*(grid_w))
            print(h*grid_h, w*grid_w, (h+1)*(grid_h), (w+1)*(grid_w))
            # 가로 세로 시작, 가로 세로 끝
            crop_img = img.crop(bbox)
            crop_img = crop_img.crop(croping_area)
            fname = "{}.png".format("{0:05d}".format(i))
            savename = save_path + fname
            crop_img.save(savename)
            print('save file ' + savename + '....')
            i += 1
 

    

#mysql에서 sedoku_table 스키마를 생성한다.

conn = pymysql.connect( host = 'localhost', user = 'root', password = '1417', charset='utf8') # database server 접속 코드
cousor = conn.cursor() #cousor 로 연동 코드
cousor.execute('create database sedoku_table;') # database server 에 (sedoku _ table) 스키마를 생성 코드
cousor.execute('use sedoku_table;')
cousor.execute(f'CREATE TABLE sedoku (id INT(16) NOT NULL AUTO_INCREMENT,dif VARCHAR(100) NOT NULL,sedoku_table VARCHAR(100) not NULL,PRIMARY KEY(id));') # 스키마에 들어가는 각요소들을 선언한다.
 #sedoku_table 스키마 사용 선언
conn.commit()
     

#코드 끝 --

dif = ['easy','medium','hard']
for i in range(3):
    for _ in range(5):
        url = f"https://sudoku.com/{dif[i]}/"
        chrome_ver = chromedriver_autoinstaller.get_chrome_version().split('.')[0]  #크롬드라이버 버전 확인

        try:
            driver = webdriver.Chrome(f'./{chrome_ver}/chromedriver.exe')   
        except:
            chromedriver_autoinstaller.install(True)
            driver = webdriver.Chrome(f'./{chrome_ver}/chromedriver.exe')

        driver.implicitly_wait(10)


        driver.get(url)

        pyautogui.click(x=305, y=677)
        sleep(0.5)

        element1 = driver.find_element_by_class_name('game') 
        element_png = element1.screenshot_as_png 
        with open("test1.png", "wb") as file: 
            file.write(element_png)

        driver.close()

        #스도쿠테이블을 생성하고 이미지인식을 통해 확인한후 문자열을 생성하는 코드 --
        sedoku_table = ['0' for i in  range(0,81)]
        pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

        image_crop('test1.png', 'C:/Users/deao3/OneDrive/문서/GitHub/c_project2/image/')
        for j in range(0,10):
            text = pytesseract.image_to_string(Image.open(f"C:/Users/deao3/OneDrive/문서/GitHub/c_project2/image/0000{j}.png"),config='--psm 6')
            try:
                sedoku_table[j] = str(int(text[0]))
            except ValueError:
                pass
            
        for j in range(10,81):
            text = pytesseract.image_to_string(Image.open(f"C:/Users/deao3/OneDrive/문서/GitHub/c_project2/image/000{j}.png"),config='--psm 6')
            try:
                sedoku_table[j] = str(int(text[0]))
            except ValueError:
                pass
        table = ''.join(sedoku_table)
        print(table)
        cousor.execute(f'INSERT INTO sedoku (dif, sedoku_table) VALUES ("{dif[i]}","{table}");')
        conn.commit()

        #코드 끝 -- 
print(":> end")
conn.commit()
conn.close() 
