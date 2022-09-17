#------------------------------------------------------------------------------
#
# file includes project sources and headers folder
#
#------------------------------------------------------------------------------

SOURCES =	src/main.c				\
			src/driver.c			\
			src/pressure_sensor.c	\
			src/alarm_monitor.c		\
			src/main_algorithm.c	\
			src/alarm_actuator.c	\
			src/startup.c

# Add your include paths to this variable
INCLUDES = -I./inc
