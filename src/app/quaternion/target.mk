QT5_PORT_DIR := $(call select_from_ports,qt5)
QT5_CONTRIB_DIR := $(QT5_PORT_DIR)/src/lib/qt5/qt5

QUATERION_DIR := $(call select_from_ports,quaternion)/qmatrixclient/quaternion
QMATRIX_DIR := $(call select_from_ports,quaternion)/qmatrixclient/libqmatrixclient

QMAKE_PROJECT_PATH = $(QUATERION_DIR)/client
QMAKE_PROJECT_FILE = $(QUATERION_DIR)/quaternion.pro

SRC_CC += content-repo.cpp \
	  voip.cpp \
	  create_room.cpp \
	  login.cpp \
	  receipts.cpp \
	  leaving.cpp \
	  room_send.cpp \
	  account-data.cpp \
	  joining.cpp \
	  logout.cpp \
	  to_device.cpp \
	  tags.cpp \
	  inviting.cpp \
	  room_state.cpp \
	  kicking.cpp \
	  banning.cpp \
	  redaction.cpp \
	  message_pagination.cpp \
	  profile.cpp \
	  location.cpp

SRC_CC += location.cpp \
	  protocol.cpp \
	  user.cpp \
	  auth_data.cpp \
	  client_device.cpp \
	  event_filter.cpp \
	  public_rooms_response.cpp \
	  push_condition.cpp \
	  push_rule.cpp \
	  push_ruleset.cpp \
	  sync_filter.cpp \
	  user_identifier.cpp \
	  homeserver.cpp \
	  identity_server.cpp \
	  room_event_filter.cpp \
	  request_email_validation.cpp \
	  request_msisdn_validation.cpp \
	  sid.cpp

INC_DIR += $(QMATRIX_DIR)/lib \
           $(QMATRIX_DIR)/lib/csapi \
           $(QMATRIX_DIR)/lib/csapi/definitions \
           $(QMATRIX_DIR)/lib/csapi/definitions/wellknown \
	   $(QMATRIX_DIR)/lib/events \
	   $(QMATRIX_DIR)/lib/jobs \
	   $(QMATRIX_DIR)/lib/application-service/definitions \
	   $(QMATRIX_DIR)/lib/identity/definitions

vpath %.cpp \
    $(QMAKE_PROJECT_PATH) \
    $(QMAKE_PROJECT_PATH)/models \
    $(QMATRIX_DIR)/lib \
    $(QMATRIX_DIR)/lib/csapi \
    $(QMATRIX_DIR)/lib/csapi/definitions \
    $(QMATRIX_DIR)/lib/csapi/definitions/wellknown \
    $(QMATRIX_DIR)/lib/events \
    $(QMATRIX_DIR)/lib/jobs \
    $(QMATRIX_DIR)/lib/application-service/definitions \
    $(QMATRIX_DIR)/lib/identity/definitions

include $(call select_from_repositories,src/app/qt5/tmpl/target_defaults.inc)
include $(call select_from_repositories,src/app/qt5/tmpl/target_final.inc)

LIBS += qt5_component qt5_network qt5_quick stdcxx libc

CC_CXX_OPT_STD = -std=gnu++14
CC_CXX_WARN_STRICT =
