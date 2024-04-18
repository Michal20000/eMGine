#include "EntityView.hpp"
#include "EntityEngine.hpp"



EntityView::EntityView(EntityEngine& entity_engine, uint16_t* table_begin, uint16_t* table_end) :
m_EntityEngine(entity_engine),
m_TableCurrent(table_begin),
m_TableEnd(table_end)
{
	while (m_TableCurrent < m_TableEnd) {
		m_RecordCurrent = 0;
		m_RecordEnd = m_EntityEngine.m_Tables[*m_TableCurrent].m_Entities.Length();
		if (m_RecordCurrent < m_RecordEnd) break;
		m_TableCurrent += 1;

	}

}



bool EntityView::Verify()
{
	// ECHO_FL_ERROR(m_TableCurrent);
	// ECHO_FL_ERROR(m_TableEnd);
	// ECHO_FL_ERROR(m_RecordCurrent);
	// ECHO_FL_ERROR(m_RecordEnd);
	// ECHO_FL_ERROR((m_TableCurrent < m_TableEnd));
	// LOG("");
	// LOG_WARN("Table=" << m_TableCurrent << "; Record=" << m_RecordCurrent << ";");
	// LOG_WARN("TableEnd=" << m_TableEnd << "; RecordEnd=" << m_RecordEnd << ";");
	return m_TableCurrent < m_TableEnd;

}
void EntityView::operator++()
{
	m_RecordCurrent += 1;
	while (m_RecordCurrent >= m_RecordEnd) [[unlikely]] {
		m_TableCurrent += 1;
		if (m_TableCurrent >= m_TableEnd) break;
		m_RecordCurrent = 0;
		m_RecordEnd = m_EntityEngine.m_Tables[*m_TableCurrent].m_Entities.Length();

	}

}
void EntityView::operator++(int32_t)
{
	m_RecordCurrent += 1;
	while (m_RecordCurrent >= m_RecordEnd) [[unlikely]] {
		m_TableCurrent += 1;
		m_RecordCurrent = 0;
		m_RecordEnd = m_EntityEngine.m_Tables[*m_TableCurrent].m_Entities.Length();

	}

}
Entity EntityView::Record()
{
	// ECHO_FL_ERROR(m_EntityEngine.m_Tables[*m_TableCurrent].m_Entities.Length());
	// ECHO_FL_ERROR(m_RecordCurrent);
	// ECHO_FL_ERROR(m_TableCurrent);
	// ECHO_FL_ERROR(m_TableEnd);
	// ECHO_FL_ERROR(m_RecordCurrent);
	// ECHO_FL_ERROR(m_RecordEnd);
	return m_EntityEngine.m_Tables[*m_TableCurrent].m_Entities[m_RecordCurrent];

}
