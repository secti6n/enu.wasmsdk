/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <enulib/system.h>

extern "C" {
   /**
    * @defgroup actionapi Action API
    * @ingroup contractdev
    * @brief Define API for querying action properties
    *
    */

   /**
    * @defgroup actioncapi Action C API
    * @ingroup actionapi
    * @brief Define API for querying action properties
    *
    *
    * An Enumivo action has the following abstract structure:
    *
    * ```
    *   struct action {
    *     scope_name scope; // the contract defining the primary code to execute for code/type
    *     action_name name; // the action to be taken
    *     permission_level[] authorization; // the accounts and permission levels provided
    *     bytes data; // opaque data processed by code
    *   };
    * ```
    *
    * This API enables your contract to inspect the fields on the current action and act accordingly.
    *
    * Example:
    * @code
    * // Assume this action is used for the following examples:
    * // {
    * //  "code": "eos",
    * //  "type": "transfer",
    * //  "authorization": [{ "account": "inita", "permission": "active" }],
    * //  "data": {
    * //    "from": "inita",
    * //    "to": "initb",
    * //    "amount": 1000
    * //  }
    * // }
    *
    * char buffer[128];
    * uint32_t total = read_action(buffer, 5); // buffer contains the content of the action up to 5 bytes
    * print(total); // Output: 5
    *
    * uint32_t msgsize = action_size();
    * print(msgsize); // Output: size of the above action's data field
    *
    * require_recipient(N(initc)); // initc account will be notified for this action
    *
    * require_auth(N(inita)); // Do nothing since inita exists in the auth list
    * require_auth(N(initb)); // Throws an exception
    *
    * print(current_time()); // Output: timestamp (in microseconds since 1970) of current block
    *
    * @endcode
    *
    *
    * @{
    */

   /**
    *  Copy up to @ref len bytes of current action data to the specified location
    *  @brief Copy current action data to the specified location
    *  @param msg - a pointer where up to @ref len bytes of the current action data will be copied
    *  @param len - len of the current action data to be copied, 0 to report required size
    *  @return the number of bytes copied to msg, or number of bytes that can be copied if len==0 passed
    */
   uint32_t read_action_data( void* msg, uint32_t len );

   /**
    * Get the length of the current action's data field
    * This method is useful for dynamically sized actions
    * @brief Get the length of current action's data field
    * @return the length of the current action's data field
    */
   uint32_t action_data_size();

   /**
    *  Add the specified account to set of accounts to be notified
    *  @brief Add the specified account to set of accounts to be notified
    *  @param name - name of the account to be verified
    */
   void require_recipient( account_name name );

   /**
    *  Verifies that @ref name exists in the set of provided auths on a action. Throws if not found
    *  @brief Verify specified account exists in the set of provided auths
    *  @param name - name of the account to be verified
    */
   void require_auth( account_name name );
   bool has_auth( account_name name );

   /**
    *  Verifies that @ref name exists in the set of provided auths on a action. Throws if not found
    *  @brief Verify specified account exists in the set of provided auths
    *  @param name - name of the account to be verified
    *  @param permission - permission level to be verified
    */
   void require_auth2( account_name name, permission_name permission );

   bool is_account( account_name name );

   /**
    *  Send an inline action in the context of this action's parent transaction
    * @param serialized_action - serialized action
    * @param size - size of serialized action in bytes
    */
   void send_inline(char *serialized_action, size_t size);

   /**
    *  Send an inline context free action in the context of this action's parent transaction
    * @param serialized_action - serialized action
    * @param size - size of serialized action in bytes
    */
   void send_context_free_inline(char *serialized_action, size_t size);

   /**
    *  Verifies that @ref name exists in the set of write locks held on a action. Throws if not found
    *  @brief Verifies that @ref name exists in the set of write locks held
    *  @param name - name of the account to be verified
    */
   void require_write_lock( account_name name );

   /**
    *  Verifies that @ref name exists in the set of read locks held on a action. Throws if not found
    *  @brief Verifies that @ref name exists in the set of read locks held
    *  @param name - name of the account to be verified
    */
   void require_read_lock( account_name name );

   /**
    *  Returns the time in microseconds from 1970 of the publication_time
    *  @brief Get the publication time
    *  @return the time in microseconds from 1970 of the publication_time
    */
   uint64_t  publication_time();

   /**
    *  Get the current receiver of the action
    *  @brief Get the current receiver of the action
    *  @return the account which specifies the current receiver of the action
    */
   account_name current_receiver();
   ///@ } actioncapi
}
