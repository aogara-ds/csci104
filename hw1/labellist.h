#ifndef LABELLIST_H
#define LABELLIST_H
#include <iostream>
#include <vector>
#include <string>

/**
 * @brief List of labelled messages
 * 
 * Allows for insertion and removal without shifting (i.e. pointers remain
 * valid to their referenced nodes after insertion/removal from the list) AND
 * fast traversal through different labels (without search).
 * 
 * Essentially, each message node can be a part of multiple labels and each label
 * is a separate doubly-linked list to provide fast traversal.  This leads to each
 * node having an array of next/previous pointers.
 */
class LabelList
{
public:
	/// Type for each "message"
	typedef std::string MsgType;
	/// Type for each "label"
	typedef std::string LabelType;

private:
	// *Forward declaration* so we can declare pointers of 
	// this type but not define the type yet. See
	// https://en.cppreference.com/w/cpp/language/class for more details.
	struct MsgNode;

	/// Type for vector of pointers to MsgNodes
	typedef std::vector<MsgNode*> NodeVec;

	/**
	 * @brief Models a node in the LabelList
	 * 
	 */
	struct MsgNode
	{ 
		MsgType msg_;  // actual message content
		std::vector<bool> labelled_; // true/false membership flag per label
		NodeVec next_; // array of ptrs to next msg per label
		NodeVec prev_; // array of ptrs to prev msg per label
		/**
		 * @brief Construct a new Msg Node object that has only 1 next/prev
		 *        pointer (i.e. is a member of the "all" label)
		 * 
		 *        next_ = nullptr
		 *        prev_ = last item on all
		 *        labelled_[0] = true
		 * 
		 * @param msg Actual message content
		 */
		// MsgNode Constructor Function
		MsgNode(const MsgType& msg);

		// ---- Add any helper functions here -----

	};

public:
	/**
	 * @brief Access token provided to the client to access a message
	 * and perform future labelling actions without giving access to
	 * internal implementation (next/prev pointers)
	 */
	class MsgToken {
		// Allow the LabelList class to access private MsgToken members
		friend class LabelList;
	private:
		// ------ Data Members ------
		MsgNode* node_;   /// Pointer to the MsgNode to retrieve data
		LabelList* list_; /// Pointer to the list this message is a member of
						  /// so we can map labels to index levels
		/**
		 * @brief Private initializing constructor to be used by LabelList 
		 *        member functions.
		 * 
		 * @param node Pointer to the node this token will reference
		 * @param list the list that the node is a member of
		 */
		MsgToken(MsgNode* node, LabelList* list);

	public:
		/**
		 * @brief Constructs an invalid MsgToken.  It must subsequently be
		 *        assigned with a valid token returned by one of the opertions
		 *        defined below.
		 */
		MsgToken();

		/**
		 * @brief checks if two MsgToken's do (operator==) or 
		 *        do NOT (operator!=) reference the same message (MsgNode)
		 * 
		 * @param rhs MsgToken to the message to compare with "this" message
		 * @return true The two MsgTokens do (==) / do NOT (!=) reference 
		 *              the same message
		 * @return false, otherwise
		 */
		bool operator==(const MsgToken& rhs) const;
		bool operator!=(const MsgToken& rhs) const;

		/**
		 * @brief Allows a MsgToken to be implicitly used (cast) to a bool
		 * 
		 * @return true if the token points to a valid MsgNode
		 * @return false if the token points to a null MsgNode
		 */
		operator bool() const;

		/**
		 * @brief Advances the pointer to the referenced node to the 
		 *        next/previous message with the given label
		 * 
		 * @param label specifies the list to traverse
		 * @return MsgToken&  returns this object for chained operations
		 * @throws std::invalid_argument if an invalid label is passed or
		 *         this message is not a member of the given label
		 */
		MsgToken& next(const LabelType& label);
		MsgToken& prev(const LabelType& label);
	
		/**
		 * @brief Determines if this message is a member of the given label
		 * @throws No-throw guarantee
		 */
		bool isLabelMember(const LabelType& label) const;

		/**
		 * @brief Ostream operator for outputting the underlying message
		 *        referenced by the MsgToken.  Do NOT output a newline or
		 *        other text before or after the message.
		 * 
		 * @param ostr  Stream to which the message should be output
		 * @param token Token referencing the message to be output
		 * @return std::ostream& ostr
		 */
		friend std::ostream& operator<<(std::ostream& ostr, const MsgToken& token); 

		/**
		 * @brief Const and non-const accessors to the message
		 * 
		 * @return MsgType const& 
		 * @throw std::logic_error if the token references an invalid message
		 */
		MsgType const& msg() const;
		MsgType & msg();

	private:
		/**
		 * @brief Helper function to ensure the referenced message is valid
		 */
		bool isValid() const;
		/**
		 * @brief Helper function check if the referenced message is a member
		 *        of the given label index
		 */
		bool isLabelMember(size_t index) const;
	};

public:
	/**
	 * @brief Construct a new Label List object with an "all" label
	 * 
	 */
	LabelList();

	/**
	 * @brief Destroy the Label List object
	 * 
	 * DONE:
	 *      Don't need to deallocate heads_ or labels_ vectors
	 *      because vectors are automatically deallocated. 
	 * 
	 * TODO:
	 *      Deallocate the linked lists themselves within ~LabelList(). 
	 * 
	 */
	~LabelList();

	/**
	 * @brief Resets the contents of the list to an empty state
	 *        deallocating existing messages.
	 * Complexity:  O(n)
	 * 
	 */
	void clear();

	/**
	 * @brief Returns true if no messages are in the "all" list
	 * Complexity:  O(1)
	 * 
	 */
	bool empty() const;

	/**
	 * @brief Returns the total number of messages in the list
	 * 
	 * Complexity:  O(n)
	 * 
	 * @return size_t 
	 * @throw No throw guarantee
	 */
	size_t size() const;

	/**
	 * @brief Add a new message to the "all" list
	 * 
	 * Complexity:  O(1)
	 * 
	 * 
	 * @param msg Contents of the new message
	 * @return MsgToken to the newly added message
	 */
	MsgToken add(const MsgType& msg);

	/**
	 * @brief Removes and deletes the message referenced by the given token
	 *        updating all lists that this message was a member of.
	 *        If an invalid token is passed, do NOTHING and simply return.
	 * Complexity:  O(|L|), where |L| is the number of unique labels
	 * 
	 * @param token Token to the message to remove
	 */
	void remove(const MsgToken& token);

	/**
	 * @brief Adds the referenced message to a given label, if not already. 
	 *        If the label does not exist, a new entry/list for it will be
	 *        created and the referenced message will be added.
	 * Complexity:  O(|L|), where |L| is the number of unique labels
	 * 
	 * @param token Token to the message to be labelled
	 * @param label Label to use
	 * @throw std::invalid_argument if the token references an invalid message
	 */
	void label(const MsgToken& token, const LabelType& label);

	/**
	 * @brief Removes the referenced message from a given label and its list. 
	 *        Attempting to remove a message from the "all" label should have
	 *        no effect.
	 * Complexity:  O(|L|), where |L| is the number of unique labels
	 * 
	 * @param token Token to the message to be unlabelled
	 * @param label Label that should be removed from the referenced message
	 * @throw std::invalid_argument if the token references an invalid message
	 * @throw std::out_of_range if a non-existent label is provided
	 * 
	 */
	void unlabel(const MsgToken& token, const LabelType& label);

	/**
	 * @brief Returns a token to the message whose content matches the given
	 *        message content or the end() token if no such message exists.
	 * Complexity:  O(|L|+|mL|), where |L| is the number of unique labels
	 *                          and |mL| is the number of messages with that label
	 * 
	 * @param msg Content to be found in the given label list
	 * @param label Label of the list that should be searched
	 * @throw std::out_of_range if a non-existent label is provided
	 */
	MsgToken find(const MsgType& msg, const LabelType& label);

	/**
	 * @brief Returns a token to the message whose position/index matches the 
	 *        specified index or the end() token if the index is invalid
	 * Complexity:  O(|L|+index), where |L| is the number of unique labels
	 * 
	 * @param index 0-based index of the desired message in the given label's 
	 *              list
	 * @param label Label of the list that should be searched
	 * @throw std::out_of_range if a non-existent label is provided
	 */
	MsgToken find(size_t index, const LabelType& label);

	/**
	 * @brief Prints the messages of a specific label list to the
	 *        provided ostream
	 * Complexity:  O(|L|+|mL|), where |L| is the number of unique labels
	 *                          and |mL| is the number of messages with that label
	 * 
	 * @param ostr Ostream to output messages to
	 * @param label List to output
	 * @param separator Character to separate subsequent messages
	 * 
	 * @throw std::out_of_range if a non-existent label is provided
	 */
	void print(std::ostream& ostr, const LabelType& label, char separator=' ') const;

	/**
	 * @brief Returns the end token which indicates and invalid token
	 *        and can be used to compare other message tokens against.
	 * Complexity:  O(1)
	 * 
	 * @return MsgToken const& to the "end" (invalid) token
	 */
	MsgToken const & end() const;

private:
	/// Constant to be returned by findLabelIndex to indicate a 
	///  label doesn't exist
	static const size_t INVALID_LABEL = (size_t)-1;
	/// Returned by end() and and when an invalid token should be returned
	static const MsgToken end_;

	/**
	 * @brief Get the level/index in the head_/next_/prev_ pointer vectors
	 *        of the specified label. This version will throw an exception
	 *        if the label does not exist, whereas findLabelIndex does not.
	 * 
	 *        This is for methods like, find messages with label. 
	 * 
	 * @param label Label to find the index of
	 * @return size_t index of the given label
	 * @throw std::out_of_range if the given label does not exist
	 */
	size_t getLabelIndex(const LabelType& label) const;

	/**
	 * @brief Get the level/index in the head_/next_/prefv_ pointer vectors
	 *        of the specified label. This version will NOT throw an exception
	 *        if the label does not exist but simply return INVALID_LABEL.
	 * 
	 * @param label Label to find the index of
	 * @return size_t index of the given label
	 */
	size_t findLabelIndex(const LabelType& label) const;

	// ---- Add private helper functions here -----

	bool checkNodeVecLen(NodeVec v, size_t index);
	bool checkBoolVecLen(std::vector<bool> v, size_t index);
	void extendNodeVec(NodeVec& v, size_t index, MsgNode* node);
	void extendBoolVec(std::vector<bool>& v, size_t index, bool value); // TODO: Maybe vector<bool> (no &)?
	MsgNode* findPrevLabelledNode(const MsgToken& token, LabelType label);
	MsgNode* findNextLabelledNode(const MsgToken& token, LabelType label);


/// Data members
private:
	NodeVec heads_; // array of ptrs to next msg per label
	std::vector<LabelType> labels_; // Stores labels and the index
									// of a label in this vector is
									// the index/level to be used
									// for node next/prev pointers

	// ---- Add additional data members here, as desired ----

};

#endif