

public:

ReturnValue psi_pedro_is_connected();

ReturnValue psi_pedro_connect(Object *&, Object *&);

ReturnValue psi_pedro_disconnect();

ReturnValue psi_pedro_subscribe(Object *&, Object *&);

ReturnValue psi_pedro_unsubscribe(Object *&, Object *&);

ReturnValue psi_pedro_notify(Object *&);

ReturnValue psi_pedro_register(Object *& reg);

ReturnValue psi_pedro_is_registered();

ReturnValue psi_pedro_deregister();

ReturnValue psi_thread_handle(Object*& handle_obj);

ReturnValue psi_pedro_address(Object*& port_obj);

ReturnValue psi_pedro_port(Object*& port_obj);

ReturnValue psi_local_p2p(Object*& thread_obj, Object*& msg_obj);

ReturnValue psi_set_default_message_thread(Object*& thread_name);

ReturnValue psi_default_message_thread(Object*& thread_name);
