/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <functional>
#include <optional>
#include <forward_list>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <cstring>
#include <cmath>
#include <string>
#include <iterator>
#include <random>
#include <iterator>
#include <chrono>
#include <thread>
// #include <cuchar>
#include <iostream>
#include <future>
#include <cmath>

/***************************
 * TODO: use and test
 ***************************/

std::size_t learn(long double weight) noexcept{
	return (std::size_t)(50 / (1 + std::cosh((weight-115) / 20)));
}

//long double sigmoid(long double x) noexcept{
//	return 1/(1+std::exp(-x));
//}

template<typename T>
class TypeDeducer;

constexpr auto DURATION_SLOW = std::chrono::duration<double>(std::chrono::seconds(15));
constexpr auto INFINITE_DURATION = DURATION_SLOW*100000;//std::chrono::duration<double>(std::numeric_limits<double>::infinity());


auto get_duration_for_weight(std::size_t weight) noexcept{
	if(weight > 110){
		return INFINITE_DURATION;
	}else{
		return DURATION_SLOW*(weight/110.0);
	}
}
auto read_l =
    []{
        std::string ret;
        std::cin >> std::ws;
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, ret);


        ret.erase(
            std::find_if(ret.crbegin(), ret.crend(),
                [](const auto c){ return !std::isspace(c);}
            ).base(),
            ret.cend()
        );
        return ret;
    };

std::future<std::string> fut;
std::optional<std::string> timed_input(std::size_t weight) noexcept{

	fut = std::async(std::launch::async, read_l);

    std::future_status status = fut.wait_for(get_duration_for_weight(weight));


    switch(status){
        case std::future_status::ready: {
            return fut.get();
        } break;
        case std::future_status::timeout: {
            return std::nullopt;
        } break;
        default: std::cerr << "Invalid future state" << std::endl;
    }
    std::terminate();
}
// template<typename Iter>
// struct reversed_range{
//     using iterator = std::reverse_iterator<Iter>;
//     using value_type = typename iterator::value_type;

//     explicit reversed_range(Iter begin, Iter end): m_begin(end), m_end(begin){}

//     iterator begin() const noexcept{
//         return m_begin;
//     }
//     iterator end() const noexcept{
//         return m_end;
//     }

// private:
//     iterator m_begin, m_end;
// };

// template<typename Iter>
// auto reversed(Iter begin, Iter end){
//     return reversed_range<Iter>(begin, end);
// }

// struct print_string_reverse{
//     std::string::reverse_iterator wrapped;
//     using value_type = const char*;
//     using difference_type = std::size_t;
//     using iterator_category = std::forward_iterator_tag;
//     using pointer = value_type;
//     using reference = value_type;

//     char result[3];

//     print_string_reverse(std::string::reverse_iterator iter): wrapped{iter}{}

//     print_string_reverse& operator++() noexcept{
//         wrapped += 2;
//         return *this;
//     }

//     print_string_reverse operator++(int) noexcept{
//         auto copy = *this;
//         this->operator++();
//         return copy;
//     }

//     reference operator*() noexcept{
//         result[2] = '\0';
//         result[1] = *wrapped;
//         result[0] = *(std::next(wrapped));

//         return result;
//     }
//     bool operator==(const print_string_reverse& other) const noexcept{
//         return wrapped == other.wrapped;
//     }
//     bool operator!=(const print_string_reverse& other) const noexcept{
//         return !(this->operator==(other));
//     }
// };

template<typename T>
struct TypeDeducer;

void clear_terminal() noexcept{
    std::cout << "\033[2J\033[1;1H";
}

using load_input_t = std::true_type;
using flashcards_input_t = std::false_type;

constexpr bool load_v = true;
constexpr bool flachcards_v = false;

template<class...> constexpr bool true_t = true; // replacement of void_t

template<typename Container>
auto operator<<(std::ostream& out, Container&& vec) ->
    std::enable_if_t<
        true_t<
            decltype(std::cbegin(vec)),
            decltype(std::cend(vec))
        >
        && !std::is_convertible_v<Container, std::string_view>,
        std::ostream&
    >
{
//    out << "[";
    if(vec.empty()) return out;

    out << *std::cbegin(vec);
    std::for_each(std::next(std::cbegin(vec)), std::cend(vec),
        [&out](const auto& t){
            out << ", " << t;
        }
    );
//    out << "] ";
    return out;
}


template<typename... Ts>
std::ostream& operator<<(std::ostream& out, const std::tuple<Ts...>& tup){
	return std::apply( [&out](auto&... args) -> std::ostream& { ((out << args), ...); return out;}, tup);
}

bool read_one(std::istream& in, std::string& into, const char delimiter, load_input_t){
    in >> std::ws;
    if(!std::getline(in, into, delimiter)){
        return false;
    }

    into.erase(
        std::find_if(into.crbegin(), into.crend(),
            [](const auto c){ return !std::isspace(c);}
        ).base(),
        into.cend()
    );
    return static_cast<bool>(in);
}

bool read_one(std::istream& in, std::string& into, const char delimiter, flashcards_input_t){
    if(!std::getline(in, into, delimiter)){
        return false;
    }
    return static_cast<bool>(in);
}

template<bool b>
bool read(std::istream& in, std::string& key, std::vector<std::string>& value){
    std::string tmp;
    std::bool_constant<b> tag;

    if(!read_one(in, key,      ':', tag)) return false;
    if(!read_one(in, tmp,      ';', tag)) return false;

    std::istringstream defs_tmp_read(tmp);

    while(read_one(defs_tmp_read, tmp, ',', tag)){
    	value.push_back(tmp);
    }

    return static_cast<bool>(in);
}

// using FlashcardsContType = std::unordered_map<std::string, std::pair<unsigned, std::forward_list<std::string>>>;

using FlashcardsContType = std::unordered_map<std::string, std::tuple<unsigned, std::vector<std::string>>>;

void clear(const char* name){
    static std::ofstream clearer;
    clearer.open(name);
    clearer.close();
}

class FlashcardApp{

    std::fstream flash_file;
    std::ifstream load_file;
    const char* load_name, *flash_name;

    std::size_t total_weights=0;

    FlashcardsContType flashcards;

    enum TupleIndex{
    	WeightIndex = 0, DefinitionsIndex = 1
    };

    enum struct RedoStatus{
    	redo, done,
    };

public:

    bool has_quit = false;
    bool do_clear = true;

    FlashcardApp(const char* name, const char* load_name)
        : flash_file(name, std::ios::in),
        load_file(load_name),
        load_name(load_name),
        flash_name(name)
    {
        std::string key;
        std::vector<std::string> value;

        std::unordered_set<std::string> to_be_removed;
		//std::unordered_set<std::string> in;

        while(read<load_v>(load_file, key, value))
        {
            if(value.front() != "-"){
				//if(!in.count(key)){
            	total_weights += 150;
                flashcards.emplace(std::move(key), std::make_tuple(150, std::move(value)));
                //}
            }else{
                to_be_removed.emplace(std::move(key));
                value.clear();
            }
        }

        unsigned weight = 0;

        while((flash_file >> weight) && (read<flachcards_v>(flash_file, key, value)))
        {
            if(auto where = to_be_removed.find(key);
               where != to_be_removed.end()
            )
            {
                to_be_removed.erase(where);
            }
            else {
                //if(!in.count(key)){
            	total_weights += weight;
                flashcards.emplace(std::move(key), std::make_tuple(weight, std::move(value)));
                //}
            }
        }
        load_file.close();
    }

    void quit() noexcept{
        has_quit = true;
    }


    // void add() noexcept{
    //     std::cout << "Please enter the word: ";

    //     std::string word;
    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ';');

    //     std::getline(std::cin, word);


    //     std::cout << "Please enter the definitions separated by a comma: ";

    //     std::string definition;

    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     std::getline(std::cin, definition);

    //     flashcards.emplace(std::move(word), std::move(definition));
    // }

    void print_menu() noexcept{
        std::cout << "Flashcards app:\n";

        for(auto&& [op, info]: commands){

            std::cout << std::setw(5) << op << " - "
                << std::setw(70) << std::right << info.second << std::endl;
        }
        do_clear = false;
    }

//    unsigned select(std::vector<unsigned>& disabled) noexcept{
//        unsigned selected;
//
//        static std::mt19937 gen(std::random_device{}() * std::time(nullptr));
//        static std::uniform_int_distribution<unsigned> index_dist(0, flashcards.size()-1);
//        static std::uniform_int_distribution<unsigned> weight_dist(1, 100);
//
//        do{
//            selected = index_dist(gen);
//        } while((weight_dist(gen) > std::get<WeightIndex>(flashcards[selected])) ||
//        		(std::find(disabled.cbegin(), disabled.cend(), selected) != disabled.cend())
//        );
//
//        return selected;
//
//    }

    void select(std::size_t n, std::vector<FlashcardsContType::value_type*>& selected) noexcept{
    	using namespace std::literals;
		static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch() / 1us);
		std::uniform_int_distribution<std::size_t> weight_dist(0, total_weights-1);

		for(auto& card: flashcards){
			if(weight_dist(gen) < n*std::get<WeightIndex>(card.second)){
				selected.push_back(&card);
			}
		}
    }

    auto calculate_review_size(std::size_t requested) const noexcept{
////         returns:
////           1. 75 if the number of elements < 975; else
////           2. flashcards.size()/13 if flashcards.size() > 650; else
////           3. 50 if flashcards.size() > 200; else
////           4. flashcards.size()/4

    	return std::min(requested, flashcards.size());
//        return std::min(75ul,
//                std::max((std::size_t)std::min(
//                            std::ceil(flashcards.size()/4.0),
//                            50.0
//                        ), flashcards.size()/13ul
//                ));
    }

    void test_work(std::size_t n,
    			   std::vector<FlashcardsContType::value_type*>& selected,
				   std::vector<FlashcardsContType::value_type*>& buffer_for_redos) noexcept
    {
    	clear_terminal();
		std::cout << "Get ready!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));

		std::string answer;

	//        std::vector<FlashcardsContType::value_type> disabled;
	//        disabled.reserve(n);

		do{
			for(auto selection: selected){
				clear_terminal();
				std::cout << "Definition of ";

				if(do_timed_poll(selection) == RedoStatus::redo)
					buffer_for_redos.push_back(selection);
			}

			selected = std::move(buffer_for_redos);
		} while(!selected.empty());
    }

    void teach_work(std::size_t n,
    				std::vector<FlashcardsContType::value_type*>& selection) noexcept
    {
    	std::cout << "Selections: \n";

    	unsigned i = 1;

    	for(auto selected: selection){
    		auto& word                  = selected->first;
    		auto& [weight, definitions] = selected->second;

    		std::cout << std::left << std::setw(5) << i << '\t'
    				<< std::left << std::setw(30) << word << '-'
					<< definitions << std::endl;
    		++i;
    	}

    	std::cout << "Press enter when ready to begin: " << std::flush;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void test() noexcept{
    	std::size_t requested_n;

    	std::cout << "Enter requested test size: ";
    	std::cin >> requested_n;
    	std::size_t n = calculate_review_size(requested_n);

        if(n == 0){
            std::cout << "No cards to test on." << std::endl;
            return;
        }

		std::vector<FlashcardsContType::value_type*> selected;
		std::vector<FlashcardsContType::value_type*> buffer_for_redos;

		selected.reserve(n);
		buffer_for_redos.reserve(n);
		select(n, selected);

        test_work(n, selected, buffer_for_redos);
    }

    void teach_and_test() noexcept{
    	std::size_t requested_n;

    	std::cout << "Enter requested test size: ";
    	std::cin >> requested_n;
    	std::size_t n = calculate_review_size(requested_n);

        if(n == 0){
            std::cout << "No cards to test on." << std::endl;
            return;
        }

        std::vector<FlashcardsContType::value_type*> selected;
		std::vector<FlashcardsContType::value_type*> buffer_for_redos;

		selected.reserve(n);
		buffer_for_redos.reserve(n);
		select(n, selected);

		teach_work(n, selected);

        test_work(n, selected, buffer_for_redos);
    }

    void update_for_time_out(auto& weight, const auto& definitions) noexcept{

    	std::cout << "\nTime out! Valid definitions: " << definitions << std::endl;
		weight += learn(static_cast<long double>(weight));

		if(fut.valid()){
			std::cout << "Press enter to continue: " << std::flush;
			fut.wait();
		}
    }

    void update_for_correct(auto& weight, const auto& definitions) noexcept{

    	std::cout << "Correct!" << std::endl;
		std::cout << "All possible answers: " << definitions << std::endl;
		weight -= learn(static_cast<long double>(weight));

		std::cout << "Press enter to contine: " << std::flush;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void update_for_incorrect(auto& weight, const auto& definitions) noexcept{

		std::cout << "Incorrect! Valid definitions: " << definitions << std::endl;
		weight += learn(static_cast<long double>(weight));

		std::cout << "Press enter to contine: " << std::flush;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    RedoStatus do_timed_poll(FlashcardsContType::value_type* selection) noexcept{
    	RedoStatus ret;

		auto& word                  = selection->first;
		auto& [weight, definitions] = selection->second;

		std::cout << word  << ": " << std::flush;

		if(auto answer = timed_input(weight); !answer)
		{
			update_for_time_out(weight, definitions);
			ret = RedoStatus::redo;
		}
		else if(std::find(definitions.cbegin(), definitions.cend(), std::move(*answer)) != definitions.cend()){
			update_for_correct(weight, definitions);
			ret = RedoStatus::done;
		}
		else{
			update_for_incorrect(weight, definitions);
			ret = RedoStatus::redo;

		}
		weight = std::clamp(weight, 30u, 200u);
//            std::cout << weight << std::endl
		return ret;
	}

    void poll_and_execute() noexcept{
        char command;
        bool cont = true;
        std::cout << "Enter a command: ";

        do{
        	std::cout << std::flush;
            std::cin >> command;

            auto location = commands.find(command);

            if(location != commands.cend()){
                std::invoke(location->second.first, *this);
                cont = false;
            }else{
                std::cout << "Error, invalid command, try again: ";
            }
        } while(cont);
        std::cout << std::endl;
    }

    ~FlashcardApp(){
        load_file.close();
        clear(load_name);

        flash_file.close();
        flash_file.open(flash_name, std::ios::out | std::ios::trunc);

        for(auto&& [word, info]: flashcards){
        	auto&& [weight, definitions] = info;
            flash_file << weight << word << ':' << definitions.front();

            std::for_each(
                std::next(definitions.cbegin()),
                definitions.cend(),
                [&flash_file=flash_file](const auto& def){
                    flash_file << ',' << def;
                }
            );
            flash_file << ';';
        }

        flash_file.close();
    }

    using commands_t = std::unordered_map<char, std::pair<decltype(&FlashcardApp::print_menu), const char*>>;

public:
    static commands_t commands;

};

template<typename F>
auto make_key(const char c, F&& f, const char* description) noexcept{
    return std::make_pair(c, std::make_pair(std::forward<F>(f), description));
}

FlashcardApp::commands_t FlashcardApp::commands{
    // make_key('n', &FlashcardApp::add, "makes a new flashcard"),
    make_key('h', &FlashcardApp::print_menu, "prints the help screen"),
    make_key('q', &FlashcardApp::quit, "quit the app"),
    make_key('t', &FlashcardApp::test, "tests on randomly selected cards"),
    make_key('&', &FlashcardApp::teach_and_test, "teaches the definitions of some randomly selected cards and tests"),
    // make_key('r', &FlashcardApp::remove, "remove cards")
};

#define PREFIX "/home/lambcoder/LinuxDev/Other/Flashcards/"

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    FlashcardApp app(PREFIX"flashcards.txt", PREFIX"load.txt");
    app.print_menu();

    do{
        app.poll_and_execute();
        if(app.do_clear){
            clear_terminal();
        }
        app.do_clear = true;
    } while(!app.has_quit);

    return 0;
}
// ------------------------------ Pieces of old code ---------------------------------
//        for(; n > 0; --n)
//        {
//            auto&& index = select(disabled);
//            auto&& [selection, weight, definitions] = flashcards[index];
//            disabled.push_back(index);
//
//
//            clear_terminal();
//            std::cout << "Definition of ";
//
//            // std::cout << std::string(selection.rbegin(), selection.rend());
//
//            // selection = std::string(selection.rbegin(), selection.rend());
//            // std::copy(print_string_reverse(selection.rbegin()),
//            //           print_string_reverse(selection.rend()),
//            //           std::ostream_iterator<const char*>(std::cout));
//            // std::cout << selection;
//
//            std::cout << selection;
////            auto n = selection.size();
////            for(int i = n; i > 1; i-=2){
////                const char tmp[] = {selection[i-2], selection[i-1]};
////                std::cout << tmp;
////            }
//
//            std::cout << ": " << std::flush;
//            static std::string reader;
//
//            if(auto answer = timed_input(); answer.empty())
//            {
//                std::cout << "Time out! Valid definitions: " << definitions << std::endl;
//                weight += 15;
//
//                if(fut.valid()){
//                    std::cout << "Press enter to continue: " << std::flush;
//                    fut.wait();
//                }
//            }
//            else if(std::find(definitions.cbegin(), definitions.cend(), std::move(answer)) != definitions.cend()){
//                std::cout << "Correct!" << std::endl;
//                weight -= 25;
//
//                std::cout << "Press enter to contine: " << std::flush;
//                std::getline(std::cin, reader);
//            }
//            else{
//                std::cout << "Incorrect! Valid definitions: " << definitions << std::endl;
//                weight += 25;
//
//                std::cout << "Press enter to contine: " << std::flush;
//                std::getline(std::cin, reader);
//            }
//            weight = std::clamp(weight, 30u, 230u);
////            std::cout << weight << std::endl;
//        }

//-----------------------
//            std::cout << word  << ": " << std::flush;
//            static std::string reader;
//
//            if(auto answer = timed_input(weight); !answer)
//            {
//                std::cout << "\nTime out! Valid definitions: " << definitions << std::endl;
//                weight += learn(weight);
//
//                selected.push_back(selection);
//
//                if(fut.valid()){
//                    std::cout << "Press enter to continue: " << std::flush;
//                    fut.wait();
//                }
//            }
//            else if(std::find(definitions.cbegin(), definitions.cend(), std::move(*answer)) != definitions.cend()){
//
//                std::cout << "Correct!" << std::endl;
//                std::cout << "All possible answers: " << definitions << std::endl;
//                weight -= learn(weight);
//
//                std::cout << "Press enter to contine: " << std::flush;
//                std::getline(std::cin, reader);
//            }
//            else{
//                std::cout << "Incorrect! Valid definitions: " << definitions << std::endl;
//                weight += learn(weight);
//
//                selected.push_back(selection);
//
//                std::cout << "Press enter to contine: " << std::flush;
//                std::getline(std::cin, reader);
//            }
//            weight = std::clamp(weight, 30u, 200u);
////            std::cout << weight << std::endl;
