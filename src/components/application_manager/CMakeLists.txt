if (EXTENDED_POLICY_FLAG)
  add_definitions(-DEXTENDED_POLICY)
endif()


include_directories (
  ./include/
  ../utils/include/
  ../formatters/include/
  ../protocol_handler/include/
  ../smart_objects/include/
  ../hmi_message_handler/include
  ../media_manager/include/
  ../connection_handler/include/
  ../config_profile/include/
  ../request_watchdog/include/
  ../transport_manager/include/
  ../resumption/include/
  ../rpc_base/include/
  ../../thirdPartyLibs/jsoncpp/include/
  ../../thirdPartyLibs/encryption/include/
  ../../thirdPartyLibs/MessageBroker/include
  ${CMAKE_BINARY_DIR}/src/components/
  ${CMAKE_SOURCE_DIR}/src/components/policy/src/policy/include/
  ${CMAKE_SOURCE_DIR}/src/components/policy/src/policy/usage_statistics/include/
)
if(MODIFY_FUNCTION_FLAGS)
include_directories (
  ${CMAKE_SOURCE_DIR}/src/LibVrMsp/
)
endif()

set (SOURCES
./src/application_manager_impl.cc
./src/usage_statistics.cc
./src/message.cc
./src/application_impl.cc
./src/mobile_command_factory.cc
./src/message_helper.cc
./src/hmi_command_factory.cc
./src/hmi_capabilities.cc
./src/application_data_impl.cc
./src/request_controller.cc
./src/resume_ctrl.cpp
./src/mobile_message_handler.cc
)

set (POLICIES_MANAGER
./src/policies/policy_handler.cc
./src/policies/policy_event_observer.cc
./src/policies/policy_retry_sequence.cc
./src/policies/pt_exchange_handler.cc
)

if (EXTENDED_POLICY_FLAG)
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/components/policy/src/policy/policy_table/table_struct_ext
  )
  list(APPEND POLICIES_MANAGER
    ./src/policies/pt_exchange_handler_ext.cc
    ./src/policies/pt_exchange_handler_impl.cc
  )
else ()
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/components/policy/src/policy/policy_table/table_struct
  )
  list(APPEND POLICIES_MANAGER
    ./src/policies/pt_exchange_handler_impl.cc
  )
endif ()

set (EVENT_ENGINE
./src/event_engine/event.cc
./src/event_engine/event_dispatcher.cc
./src/event_engine/event_observer.cc
)

set (MOBILE_COMMANDS_SOURCES
./src/commands/command_impl.cc
./src/commands/command_request_impl.cc
./src/commands/command_response_impl.cc
./src/commands/command_notification_impl.cc
./src/commands/pending.cc
./src/commands/mobile/add_command_request.cc
./src/commands/mobile/add_command_response.cc
./src/commands/mobile/add_sub_menu_request.cc
./src/commands/mobile/add_sub_menu_response.cc
./src/commands/mobile/alert_request.cc
./src/commands/mobile/alert_response.cc
./src/commands/mobile/alert_maneuver_request.cc
./src/commands/mobile/alert_maneuver_response.cc
./src/commands/mobile/change_registration_request.cc
./src/commands/mobile/change_registration_response.cc
./src/commands/mobile/create_interaction_choice_set_request.cc
./src/commands/mobile/create_interaction_choice_set_response.cc
./src/commands/mobile/delete_command_request.cc
./src/commands/mobile/delete_command_response.cc
./src/commands/mobile/delete_file_request.cc
./src/commands/mobile/delete_file_response.cc
./src/commands/mobile/delete_interaction_choice_set_request.cc
./src/commands/mobile/delete_interaction_choice_set_response.cc
./src/commands/mobile/delete_sub_menu_request.cc
./src/commands/mobile/delete_sub_menu_response.cc
./src/commands/mobile/dial_number_request.cc
./src/commands/mobile/encoded_sync_pdata_request.cc
./src/commands/mobile/encoded_sync_pdata_response.cc
./src/commands/mobile/end_audio_pass_thru_request.cc
./src/commands/mobile/end_audio_pass_thru_response.cc
./src/commands/mobile/generic_response.cc
./src/commands/mobile/get_dtcs_request.cc
./src/commands/mobile/get_dtcs_response.cc
./src/commands/mobile/diagnostic_message_request.cc
./src/commands/mobile/diagnostic_message_response.cc
./src/commands/mobile/get_vehicle_data_request.cc
./src/commands/mobile/get_vehicle_data_response.cc
./src/commands/mobile/list_files_request.cc
./src/commands/mobile/list_files_response.cc
./src/commands/mobile/on_app_interface_unregistered_notification.cc
./src/commands/mobile/on_audio_pass_thru_notification.cc
./src/commands/mobile/on_button_event_notification.cc
./src/commands/mobile/on_button_press_notification.cc
./src/commands/mobile/on_driver_distraction_notification.cc
./src/commands/mobile/on_encoded_sync_pdata_notification.cc
./src/commands/mobile/on_hmi_status_notification.cc
./src/commands/mobile/on_language_change_notification.cc
./src/commands/mobile/on_command_notification.cc
./src/commands/mobile/on_permissions_change_notification.cc
./src/commands/mobile/on_tbt_client_state_notification.cc
./src/commands/mobile/on_vehicle_data_notification.cc
./src/commands/mobile/perform_audio_pass_thru_request.cc
./src/commands/mobile/perform_audio_pass_thru_response.cc
./src/commands/mobile/perform_interaction_request.cc
./src/commands/mobile/perform_interaction_response.cc
./src/commands/mobile/put_file_request.cc
./src/commands/mobile/put_file_response.cc
./src/commands/mobile/read_did_request.cc
./src/commands/mobile/read_did_response.cc
./src/commands/mobile/register_app_interface_request.cc
./src/commands/mobile/register_app_interface_response.cc
./src/commands/mobile/reset_global_properties_request.cc
./src/commands/mobile/reset_global_properties_response.cc
./src/commands/mobile/scrollable_message_request.cc
./src/commands/mobile/scrollable_message_response.cc
./src/commands/mobile/set_display_layout_request.cc
./src/commands/mobile/set_display_layout_response.cc
./src/commands/mobile/set_global_properties_request.cc
./src/commands/mobile/set_global_properties_response.cc
./src/commands/mobile/set_icon_request.cc
./src/commands/mobile/set_icon_response.cc
./src/commands/mobile/set_media_clock_timer_request.cc
./src/commands/mobile/set_media_clock_timer_response.cc
./src/commands/mobile/show_constant_tbt_request.cc
./src/commands/mobile/show_constant_tbt_response.cc
./src/commands/mobile/show_request.cc
./src/commands/mobile/show_response.cc
./src/commands/mobile/slider_request.cc
./src/commands/mobile/slider_response.cc
./src/commands/mobile/speak_request.cc
./src/commands/mobile/speak_response.cc
./src/commands/mobile/subscribe_button_request.cc
./src/commands/mobile/subscribe_button_response.cc
./src/commands/mobile/subscribe_vehicle_data_request.cc
./src/commands/mobile/subscribe_vehicle_data_response.cc
./src/commands/mobile/unregister_app_interface_request.cc
./src/commands/mobile/unregister_app_interface_response.cc
./src/commands/mobile/unsubscribe_button_request.cc
./src/commands/mobile/unsubscribe_button_response.cc
./src/commands/mobile/unsubscribe_vehicle_data_request.cc
./src/commands/mobile/unsubscribe_vehicle_data_response.cc
./src/commands/mobile/update_turn_list_request.cc
./src/commands/mobile/update_turn_list_response.cc
./src/commands/mobile/sync_pdata_request.cc
./src/commands/mobile/sync_pdata_response.cc
./src/commands/mobile/system_request.cc
./src/commands/mobile/system_response.cc
./src/commands/mobile/on_sync_pdata_notification.cc
./src/commands/mobile/on_keyboard_input_notification.cc
./src/commands/mobile/on_touch_event_notification.cc
./src/commands/mobile/on_system_request_notification.cc
./src/commands/mobile/on_hash_change_notification.cc
)

set (HMI_COMMANDS_SOURCES
./src/commands/hmi/request_to_hmi.cc
./src/commands/hmi/response_from_hmi.cc
./src/commands/hmi/request_from_hmi.cc
./src/commands/hmi/response_to_hmi.cc
./src/commands/hmi/notification_to_hmi.cc
./src/commands/hmi/notification_from_hmi.cc
./src/commands/hmi/allow_all_apps_request.cc
./src/commands/hmi/allow_all_apps_response.cc
./src/commands/hmi/allow_app_request.cc
./src/commands/hmi/allow_app_response.cc
./src/commands/hmi/update_sdl_request.cc
./src/commands/hmi/update_sdl_response.cc
./src/commands/hmi/activate_app_request.cc
./src/commands/hmi/activate_app_response.cc
./src/commands/hmi/get_system_info_request.cc
./src/commands/hmi/get_system_info_response.cc
./src/commands/hmi/sdl_get_list_of_permissions_request.cc
./src/commands/hmi/sdl_get_list_of_permissions_response.cc
./src/commands/hmi/sdl_get_user_friendly_message_request.cc
./src/commands/hmi/sdl_get_user_friendly_message_response.cc
./src/commands/hmi/sdl_get_status_update_request.cc
./src/commands/hmi/sdl_get_status_update_response.cc
./src/commands/hmi/on_status_update_notification.cc
./src/commands/hmi/sdl_activate_app_response.cc
./src/commands/hmi/sdl_activate_app_request.cc
./src/commands/hmi/mixing_audio_supported_request.cc
./src/commands/hmi/mixing_audio_supported_response.cc
./src/commands/hmi/update_app_list_request.cc
./src/commands/hmi/update_app_list_response.cc
./src/commands/hmi/on_update_device_list.cc
./src/commands/hmi/update_device_list_request.cc
./src/commands/hmi/update_device_list_response.cc
./src/commands/hmi/on_sdl_consent_needed_notification.cc
./src/commands/hmi/on_exit_all_applications_notification.cc
./src/commands/hmi/on_exit_application_notification.cc
./src/commands/hmi/on_start_device_discovery.cc
./src/commands/hmi/close_popup_request.cc
./src/commands/hmi/close_popup_response.cc
./src/commands/hmi/on_app_activated_notification.cc
./src/commands/hmi/button_get_capabilities_request.cc
./src/commands/hmi/button_get_capabilities_response.cc
./src/commands/hmi/vr_is_ready_request.cc
./src/commands/hmi/vr_is_ready_response.cc
./src/commands/hmi/vr_add_command_request.cc
./src/commands/hmi/vr_add_command_response.cc
./src/commands/hmi/vr_delete_command_request.cc
./src/commands/hmi/vr_delete_command_response.cc
./src/commands/hmi/vr_change_registration_request.cc
./src/commands/hmi/vr_change_registration_response.cc
./src/commands/hmi/vr_get_supported_languages_request.cc
./src/commands/hmi/vr_get_supported_languages_response.cc
./src/commands/hmi/vr_get_language_request.cc
./src/commands/hmi/vr_get_language_response.cc
./src/commands/hmi/vr_get_capabilities_request.cc
./src/commands/hmi/vr_get_capabilities_response.cc
./src/commands/hmi/tts_is_ready_request.cc
./src/commands/hmi/tts_is_ready_response.cc
./src/commands/hmi/tts_change_registration_request.cc
./src/commands/hmi/tts_change_registration_response.cc
./src/commands/hmi/tts_get_language_request.cc
./src/commands/hmi/tts_get_language_response.cc
./src/commands/hmi/tts_get_supported_languages_request.cc
./src/commands/hmi/tts_get_supported_languages_response.cc
./src/commands/hmi/tts_stop_speaking_request.cc
./src/commands/hmi/tts_stop_speaking_response.cc
./src/commands/hmi/tts_speak_request.cc
./src/commands/hmi/tts_speak_response.cc
./src/commands/hmi/tts_set_global_properties_request.cc
./src/commands/hmi/tts_set_global_properties_response.cc
./src/commands/hmi/tts_get_capabilities_request.cc
./src/commands/hmi/tts_get_capabilities_response.cc
./src/commands/hmi/vr_perform_interaction_request.cc
./src/commands/hmi/vr_perform_interaction_response.cc
./src/commands/hmi/ui_add_command_request.cc
./src/commands/hmi/ui_add_command_response.cc
./src/commands/hmi/ui_delete_command_request.cc
./src/commands/hmi/ui_delete_command_response.cc
./src/commands/hmi/ui_add_submenu_request.cc
./src/commands/hmi/ui_add_submenu_response.cc
./src/commands/hmi/ui_delete_submenu_request.cc
./src/commands/hmi/ui_delete_submenu_response.cc
./src/commands/hmi/ui_get_supported_languages_request.cc
./src/commands/hmi/ui_get_supported_languages_response.cc
./src/commands/hmi/ui_get_language_request.cc
./src/commands/hmi/ui_get_language_response.cc
./src/commands/hmi/ui_get_capabilities_request.cc
./src/commands/hmi/ui_get_capabilities_response.cc
./src/commands/hmi/ui_change_registration_request.cc
./src/commands/hmi/ui_change_registration_response.cc
./src/commands/hmi/ui_show_request.cc
./src/commands/hmi/ui_show_response.cc
./src/commands/hmi/ui_alert_request.cc
./src/commands/hmi/ui_alert_response.cc
./src/commands/hmi/ui_slider_request.cc
./src/commands/hmi/ui_scrollable_message_request.cc
./src/commands/hmi/ui_scrollable_message_response.cc
./src/commands/hmi/ui_set_global_properties_request.cc
./src/commands/hmi/ui_set_global_properties_response.cc
./src/commands/hmi/ui_slider_response.cc
./src/commands/hmi/ui_is_ready_request.cc
./src/commands/hmi/ui_is_ready_response.cc
./src/commands/hmi/ui_perform_audio_pass_thru_request.cc
./src/commands/hmi/ui_perform_audio_pass_thru_response.cc
./src/commands/hmi/ui_end_audio_pass_thru_request.cc
./src/commands/hmi/ui_end_audio_pass_thru_response.cc
./src/commands/hmi/ui_perform_interaction_request.cc
./src/commands/hmi/ui_perform_interaction_response.cc
./src/commands/hmi/ui_set_icon_request.cc
./src/commands/hmi/ui_set_icon_response.cc
./src/commands/hmi/ui_set_media_clock_timer_request.cc
./src/commands/hmi/ui_set_media_clock_timer_response.cc
./src/commands/hmi/ui_show_request.cc
./src/commands/hmi/ui_show_response.cc
./src/commands/hmi/vi_is_ready_request.cc
./src/commands/hmi/vi_is_ready_response.cc
./src/commands/hmi/vi_read_did_request.cc
./src/commands/hmi/vi_read_did_response.cc
./src/commands/hmi/vi_get_dtcs_request.cc
./src/commands/hmi/vi_get_dtcs_response.cc
./src/commands/hmi/vi_diagnostic_message_request.cc
./src/commands/hmi/vi_diagnostic_message_response.cc
./src/commands/hmi/vi_get_vehicle_type_request.cc
./src/commands/hmi/vi_get_vehicle_type_response.cc
./src/commands/hmi/navi_is_ready_request.cc
./src/commands/hmi/navi_is_ready_response.cc
./src/commands/hmi/navi_alert_maneuver_request.cc
./src/commands/hmi/navi_alert_maneuver_response.cc
./src/commands/hmi/navi_update_turn_list_request.cc
./src/commands/hmi/navi_update_turn_list_response.cc
./src/commands/hmi/navi_show_constant_tbt_request.cc
./src/commands/hmi/navi_show_constant_tbt_response.cc
./src/commands/hmi/on_ready_notification.cc
./src/commands/hmi/on_system_context_notification.cc
./src/commands/hmi/on_device_chosen_notification.cc
./src/commands/hmi/on_allow_sdl_functionality_notification.cc
./src/commands/hmi/on_app_permission_consent_notification.cc
./src/commands/hmi/on_app_registered_notification.cc
./src/commands/hmi/on_app_permission_changed_notification.cc
./src/commands/hmi/on_app_unregistered_notification.cc
./src/commands/hmi/on_driver_distraction_notification.cc
./src/commands/hmi/on_ignition_cycle_over_notification.cc
./src/commands/hmi/on_system_info_changed_notification.cc
./src/commands/hmi/on_file_removed_notification.cc
./src/commands/hmi/on_play_tone_notification.cc
./src/commands/hmi/on_tts_started_notification.cc
./src/commands/hmi/on_tts_stopped_notification.cc
./src/commands/hmi/on_vr_started_notification.cc
./src/commands/hmi/on_vr_stopped_notification.cc
./src/commands/hmi/on_vr_command_notification.cc
./src/commands/hmi/on_ui_command_notification.cc
./src/commands/hmi/on_navi_tbt_client_state_notification.cc
./src/commands/hmi/on_app_deactivated_notification.cc
./src/commands/hmi/on_tts_language_change_notification.cc
./src/commands/hmi/on_vr_language_change_notification.cc
./src/commands/hmi/on_ui_language_change_notification.cc
./src/commands/hmi/on_button_event_notification.cc
./src/commands/hmi/on_button_press_notification.cc
./src/commands/hmi/on_find_applications.cc
./src/commands/hmi/on_ui_keyboard_input_notification.cc
./src/commands/hmi/on_ui_touch_event_notification.cc
./src/commands/hmi/on_ui_reset_timeout_notification.cc
./src/commands/hmi/navi_start_stream_request.cc
./src/commands/hmi/navi_start_stream_response.cc
./src/commands/hmi/navi_stop_stream_request.cc
./src/commands/hmi/navi_stop_stream_response.cc
./src/commands/hmi/audio_start_stream_request.cc
./src/commands/hmi/audio_start_stream_response.cc
./src/commands/hmi/audio_stop_stream_request.cc
./src/commands/hmi/audio_stop_stream_response.cc
./src/commands/hmi/on_system_request_notification.cc
./src/commands/hmi/on_put_file_notification.cc
./src/commands/hmi/on_resume_audio_source_notification.cc
./src/commands/hmi/on_sdl_close_notification.cc
./src/commands/hmi/ui_set_display_layout_request.cc
./src/commands/hmi/ui_set_display_layout_response.cc
./src/commands/hmi/on_record_start_notification.cc
./src/commands/hmi/add_statistics_info_notification.cc
./src/commands/hmi/on_system_error_notification.cc
./src/commands/hmi/basic_communication_system_request.cc
./src/commands/hmi/basic_communication_system_response.cc
./src/commands/hmi/sdl_policy_update.cc
./src/commands/hmi/sdl_policy_update_response.cc
./src/commands/hmi/on_received_policy_update.cc
./src/commands/hmi/on_policy_update.cc
./src/commands/hmi/get_urls.cc
./src/commands/hmi/get_urls_response.cc
./src/commands/hmi/on_device_state_changed_notification.cc
)
if(MODIFY_FUNCTION_FLAGS)
	list(APPEND HMI_COMMANDS_SOURCES
	./src/commands/hmi/sdl_log_notification.cc
	./src/commands/hmi/on_unsubscribebutton_notification.cc
	./src/commands/hmi/on_subscribebutton_notification.cc
	./src/commands/hmi/on_microphone_recording_notification.cc
	./src/commands/hmi/on_deleteinteractionchoiceset_notification.cc
	./src/commands/hmi/on_createinteractionchoiceset_notification.cc
  ./src/commands/hmi/on_search_applist_notification.cc
  ./src/commands/hmi/on_find_applist_notification.cc
  ./src/commands/hmi/on_vr_start_record_notification.cc
  ./src/commands/hmi/on_vr_cancel_record_notification.cc
  ./src/commands/hmi/on_vr_status_notification.cc
  ./src/commands/hmi/on_vr_cancel_notification.cc
  ./src/commands/hmi/on_vr_help_notification.cc
  ./src/commands/hmi/on_vr_exit_app_notification.cc
  ./src/commands/hmi/on_vr_switch_app_notification.cc
  ./src/commands/hmi/on_vr_command_tts_notification.cc
  ./src/commands/hmi/on_vr_result_notification.cc
  ./src/commands/hmi/on_ui_perform_audio_pass_thru_start_notification.cc
  ./src/commands/hmi/on_ui_perform_audio_pass_thru_stop_notification.cc
	)
endif()

set (HMI_COMMANDS_SOURCES_JSON
./src/commands/hmi/vi_get_vehicle_data_request.cc
./src/commands/hmi/vi_get_vehicle_data_response.cc
./src/commands/hmi/vi_subscribe_vehicle_data_request.cc
./src/commands/hmi/vi_subscribe_vehicle_data_response.cc
./src/commands/hmi/vi_unsubscribe_vehicle_data_request.cc
./src/commands/hmi/vi_unsubscribe_vehicle_data_response.cc
./src/commands/hmi/on_vi_vehicle_data_notification.cc
)

set (HMI_COMMANDS_SOURCES_DBUS
./src/commands/hmi/on_vi_gps_data_notification.cc
./src/commands/hmi/on_vi_speed_notification.cc
./src/commands/hmi/on_vi_rpm_notification.cc
./src/commands/hmi/on_vi_fuel_level_notification.cc
./src/commands/hmi/on_vi_fuel_level_state_notification.cc
./src/commands/hmi/on_vi_instant_fuel_consumption_notification.cc
./src/commands/hmi/on_vi_external_temperature_notification.cc
./src/commands/hmi/on_vi_vin_notification.cc
./src/commands/hmi/on_vi_prndl_notification.cc
./src/commands/hmi/on_vi_tire_pressure_notification.cc
./src/commands/hmi/on_vi_odometer_notification.cc
./src/commands/hmi/on_vi_belt_status_notification.cc
./src/commands/hmi/on_vi_body_information_notification.cc
./src/commands/hmi/on_vi_device_status_notification.cc
./src/commands/hmi/on_vi_driver_braking_notification.cc
./src/commands/hmi/on_vi_wiper_status_notification.cc
./src/commands/hmi/on_vi_head_lamp_status_notification.cc
./src/commands/hmi/on_vi_engine_torque_notification.cc
./src/commands/hmi/on_vi_acc_pedal_position_notification.cc
./src/commands/hmi/on_vi_steering_wheel_angle_notification.cc
./src/commands/hmi/on_vi_my_key_notification.cc
)

if (${HMI_JSON_API})
    set (HMI_COMMANDS_SOURCES ${HMI_COMMANDS_SOURCES} ${HMI_COMMANDS_SOURCES_JSON})
endif (${HMI_JSON_API})
if (${HMI_DBUS_API})
    set (HMI_COMMANDS_SOURCES ${HMI_COMMANDS_SOURCES} ${HMI_COMMANDS_SOURCES_DBUS})
endif (${HMI_DBUS_API})

SET (LIBRARIES
  UsageStatistics
  dl
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "QNX" OR CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  list(REMOVE_ITEM LIBRARIES dl)
endif()

add_library("ApplicationManager" ${SOURCES} ${MOBILE_COMMANDS_SOURCES} ${HMI_COMMANDS_SOURCES} ${POLICIES_MANAGER} ${EVENT_ENGINE})
target_link_libraries("ApplicationManager" ${LIBRARIES})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_link_libraries("ApplicationManager" HMI_API MOBILE_API v4_protocol_v1_2_no_extra)
endif()

if(ENABLE_LOG)
if(MODIFY_FUNCTION_FLAGS)
else()
  add_dependencies("ApplicationManager" liblog4cxx)
  target_link_libraries("ApplicationManager" log4cxx -L${LOG4CXX_LIBS_DIRECTORY})
endif()
endif()
