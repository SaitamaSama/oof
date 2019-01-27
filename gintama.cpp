#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

typedef struct {
  std::string username;
  std::string password;
} cred;

typedef struct {
  std::string destination;
  std::string from;
  int price;
  int available_count;
} ticket;

typedef struct {
  int id;
  std::string destination;
  std::string from;
} booked_ticket;

typedef struct {
  bool logged_in = false;
  bool is_admin = false;
  char login_attempt_authority = ' ';
  cred admin_cred;
  std::string username;
  std::vector<ticket> tickets;
  std::vector<booked_ticket> booked_tickets;
} state;

const std::vector<cred> valid_creds {
  { "admin", "default_pass" },
  { "saitama", "saitama_is_cool" }
};

void print_options(state program_state);
void print_admin_abilities(state program_state);
void print_booked_tickets(state program_state);
void print_user_abilites(state program_state);

bool check_cred(state program_state) {
  bool flag = false;
  for(const cred current_cred : valid_creds) {
    if(
      current_cred.username == program_state.admin_cred.username
      && current_cred.password == program_state.admin_cred.password
    ) {
      flag = true;
    }
  }

  return flag;
}

void print_log_in_options(void) {
  std::string login_text = "Login as [A]dministrator or [G]uest: ";
 // printf(login_text.c_str());
  std::cout << login_text;
}

void prompt_character_input(char* input_var, bool convert_to_lower = true) {
  scanf(" %c", input_var);
  *input_var = std::tolower(*input_var, std::locale());
}

state reset_state_auth(state program_state) {
  program_state.logged_in = false;
  program_state.is_admin = false;
  program_state.admin_cred.username = "";
  program_state.admin_cred.password = "";

  return program_state;
}

state print_unsuccessful_attempt(state program_state) {
  program_state = reset_state_auth(program_state);

  std::string attempt_text = "The credentials you entered are invalid.\n";
  std::cout << attempt_text;

  return program_state;
}

void print_tickets(state program_state) {
  std::cout << "Available Tickets:\n";

  if(program_state.tickets.size() == 0) {
    std::cout << "No tickets set at the moment.\n";
  }

  int index = 0;

  for(const ticket tick : program_state.tickets) {
    if(tick.available_count <= 0) continue;
    printf(
      "Index: %d\n------\nSource: %s\nDestination: %s\nPrice: %d\nAvailable Tickets: %d\n------\n",
      ++index,
      tick.from.c_str(),
      tick.destination.c_str(),
      tick.price,
      tick.available_count
    );
  }
}

void add_ticket(state program_state) {
  ticket new_ticket;
  std::cout << "Ticket, From: ";
  std::cin >> new_ticket.from;
  std::cout << "Ticket, To: ";
  std::cin >> new_ticket.destination;
  std::cout << "Ticket, Price: ";
  std::cin >> new_ticket.price;
  std::cout << "Ticket, Available Count: ";
  std::cin >> new_ticket.available_count;

  program_state.tickets.push_back(new_ticket);

  print_admin_abilities(program_state);
}

void edit_tickets(state program_state) {
  print_tickets(program_state);
  std::cout << "Current Options:\n[A]dd Ticket Type; [E]xit edit mode: ";
  char char_input;
  prompt_character_input(&char_input);

  switch(char_input) {
    case 'a':
      add_ticket(program_state);
      break;
    case 'e':
      print_admin_abilities(program_state);
      break;
  }
}

void print_admin_abilities(state program_state) {
  std::string admin_capabilites_text = "Current Options:\n[L]og Out; [E]dit tickets; [P]rint Stats: ";
  std::cout << admin_capabilites_text;
  char char_input;
  prompt_character_input(&char_input);

  switch (char_input) {
    case 'l':
      program_state = reset_state_auth(program_state);
      print_options(program_state);
      break;
    case 'e':
      edit_tickets(program_state);
      break;
    case 'p':
      print_tickets(program_state);
      print_admin_abilities(program_state);
      break;
  }
}

void print_admin_login_prompt(state program_state) {
  std::string login_prompt_username = "Username: ";
  std::string login_prompt_password = "Password: ";
  
  std::string username = "";
  std::string password = "";

  printf("%s", login_prompt_username.c_str());
  std::cin >> username;
  printf("%s", login_prompt_password.c_str());
  std::cin >> password;

  program_state.admin_cred.username = username;
  program_state.admin_cred.password = password;

  if(check_cred(program_state)) {
    program_state.is_admin = true;
    program_state.logged_in = true;
    print_admin_abilities(program_state);
  } else {
    program_state = print_unsuccessful_attempt(program_state);
    
    print_options(program_state);
  }
}

void print_booking_prompt(state program_state) {
  std::cout << "Book Tickets:\n";
  print_tickets(program_state);
  std::cout << "Enter the index of the ticket that you want to book: ";

  int id;
  std::cin >> id;
  ticket to_book_ticket = program_state.tickets[id - 1];
  booked_ticket new_ticket = {
    id,
    to_book_ticket.destination,
    to_book_ticket.from
  };

  program_state.tickets[id - 1].available_count--;

  program_state.booked_tickets.push_back(new_ticket);

  print_booked_tickets(program_state);
}

void print_booked_tickets(state program_state) {
  std::cout << "Booked Tickets:\n";

  if(program_state.booked_tickets.size() == 0) {
    std::cout << "No tickets booked yet.";
  }

  for(const booked_ticket ticket : program_state.booked_tickets) {
    printf(
      "\n------\nFrom: %s\nDestination: %s\n------\n",
      ticket.from.c_str(),
      ticket.destination.c_str()
    );
  }

  print_user_abilites(program_state);
}

void print_user_abilites(state program_state) {
  std::cout << "Current Options: [B]ook Ticket; [S]ee Booked Tickets; [A]vailable Tickets; [E]xit: ";
  char char_input;
  prompt_character_input(&char_input);

  switch(char_input) {
    case 'b':
      print_booking_prompt(program_state);
      break;
    case 's':
      print_booked_tickets(program_state);
      break;
    case 'a':
      print_tickets(program_state);
      print_user_abilites(program_state);
      break;
    case 'e':
      break;
  }
}

void handle_authority_change(state program_state, char auth) {
  program_state.login_attempt_authority = auth;
  if(auth == 'a') {
    print_admin_login_prompt(program_state);
  } else {
    program_state.is_admin = false;
    program_state.logged_in = true;
    print_user_abilites(program_state);
  }
}

void print_options(state program_state) {
  if(!program_state.logged_in) {
    // Print the options for logging in.
    print_log_in_options();

    char prompt_input;
    prompt_character_input(&prompt_input);

    handle_authority_change(program_state, prompt_input);
  }
}

void run_program_loop(void) {
  state program_state;

  do {
    std::system("clear");

    print_options(program_state);
  } while (true);
}

int main() {
  run_program_loop();

  return 0;
}