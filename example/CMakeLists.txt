# Erstellt die ausführbare Datei (BeispielApp.exe)
add_executable(BeispielApp main.cpp)

# Verknüpft die App mit deiner Library. 
# Dadurch weiß die App automatisch, wo die Header (.hpp) und die Library-Inhalte liegen.
target_link_libraries(BeispielApp PRIVATE EasyWindow)