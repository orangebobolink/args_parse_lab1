# Тестовые данные
## Успешный тест
### arrange
```json 
"args": [
  "-h",
  "--output",
  "OutputMe",
  "-o",
  "OutputMe",
  "--giveMyAge=20",
  "--isMyProgramCoolTrue"
]
```
### assert
![image](https://github.com/orangebobolink/args_parse_lab1/assets/91991278/bd33e61b-fb5c-4a35-8ff0-6382d16df592)
## Негативный тест. output обязан иметь значение
### arrange
```json 
 "args": [
   "-h",
   "--output",
   "--giveMyAge=20",
   "--isMyProgramCoolTrue"
 ]
```
### assert
![image](https://github.com/orangebobolink/args_parse_lab1/assets/91991278/6fa432dc-ec9f-44f9-9265-17d75f631589)
## Негативный тест. Аргумент не может принимать множество значений переданных разными способами
### arrange
```json 
 "args": [
  "-h",
  "--giveMyAge=20",
  "20",
  "--isMyProgramCoolTrue"
]
```
### assert
![image](https://github.com/orangebobolink/args_parse_lab1/assets/91991278/7ebd9db0-01c4-4d42-9726-c56eecdd337a)



