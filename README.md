# Proyecto2
Segundo proyecto Robótica


--Descargar proyecto
Entrar al workspace de ROS ya existente y dentro de la carpeta 'src' descargar los archivos del proyecto con 'git clone https://github.com/diegoamayaw/Proyecto2'. Subir a la carpeta del workspace, hacer 'catkin_make'y 'source devel/setup.bash'. Para probar que el programa se ejecuta correctamente, en una terminal diferente correr 'roscore' y en otra 'rosrun Proyecto2 control'.

--Ejecutar la simulacion
Abrir cuatro pestanas de terminal.

Pestana1 - En el directorio que contiene el modelo del automovil de Gazebo, descargado desde GitHub como se menciono en el archivo pdf de las especificaciones del proyecto, navegar hasta AutoNOMOS_simulation, ejecutar 'source devel/setup.bash' y 'roslaunch autonomos_gazebo empty_autonomous.launch'. Esperar a que cargue gazebo con el modelo.

Pestana2 - Navegar hasta el workspace de ROS, ejecutar 'source devel/setup.bash' y 'rosrun Proyecto2 control'. Cuando el programa pida los Herts, ingresar '10'.

Pestana3 - Ejecutar 'rostopic pub -1 /robot/next_pose geometry_msgs/Pose2D "x: 5.0
y: 5.0
theta: 0.0"' para dar una pose deseada al automovil. Ahora podra ver al automovil moviendose en Gazebo. Se puede modificar los valores de x, y y theta, asi como ejecutar este comando cuando guste para cambiar la pose deseada.

Pestana4 - Ejecutar 'rostopic echo robot/pose' para ver la posicion real del automovil con coordenadas.

El video de las pruebas relizadas se puede descargar en el siguiente link de Google Drive:

https://drive.google.com/open?id=1FYZ_Bcuzai2EVxlVqrDa7vW9cO6Y1gl8




