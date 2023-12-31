/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"Queue.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */
bool Enqueue(queue_t *q, int16_t data)
{
	if( q->num >= SIZE )	return false;

	q->data[ (q->head + q->num) % SIZE ] = data;
	q->num++;
	return true;
}


bool Dequeue(queue_t *q, int16_t *data)
{
	if( q->num == 0 )	return false;

	*data = q->data[ q->head ];
	q->head = (q->head + 1) % SIZE;
	q->num--;
	return true;
}