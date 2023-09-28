#ifndef OF_RANDOM_HPP_
#define OF_RANDOM_HPP_

#include <glm/glm.hpp>
#include <random>

#include "ofSingleton.h"
#include "ofMath.h"

namespace of::random {

// https://stackoverflow.com/questions/25360241/using-random-number-generator-multiple-instances-or-singleton-approach
// https://simplecxx.github.io/2018/11/03/seed-mt19937.html

/// \class of::random::Engine
///
/// An mt19937 instance wrapped in a singleton, with default non-deterministic seeding
/// A balance is aimed between ease-of-use, and versatility, and minimize reliance on advanced concepts
/// (e.g. the lib is templated, but default usage does not require template parameters)
/// The goal is to have a centralized, thread-safe source of randomness that can be deterministic or not.
///
class Engine : public of::utils::Singleton<Engine> {

	std::random_device rd_ {};
	std::seed_seq seq_ { rd_(), rd_(), rd_(), rd_() }; // 4 is considered fine for non-cryptographic needs
	std::mt19937 gen_ { seq_ };
	bool deterministic_ { false }; // by default the degine is non-deterministic (unpredictable)

public:
	/// return the generator for use in random distributions or functions
	///
	/// \returns a reference to the mt19937 generator
	auto & gen() { return gen_; }

	/// passes a value to seed the mt19937 generator
	void seed(unsigned long new_seed) {
		deterministic_ = true;
		gen_.seed(new_seed);
	}

	/// \returns true or fall depending if the engine has been seeded with a deterministic value
	auto is_deterministic() const { return deterministic_; }
};

/// \returns a reference to the engine instance
inline auto engine() {
	return of::random::Engine::instance();
}

/// \returns a reference to the generator within the engine instance
inline auto & gen() {
	return of::random::Engine::instance()->gen();
}

/// Passes a value to seed the mt19937 generator within the engine instance
inline void seed(unsigned long seed) {
	of::random::Engine::instance()->seed(seed);
}

} // end namespace of::random

#endif // OF_RANDOM_HPP_
