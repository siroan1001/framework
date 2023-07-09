#include "MeshBuffer.h"

MeshBuffer::MeshBuffer(const Description& desc)
	: m_pVtxBuffer(NULL), m_pIdxBuffer(NULL), m_desc{}
{
	HRESULT hr = E_FAIL;
	hr = CreateVertexBuffer(desc.pVtx, desc.vtxSize, desc.vtxCount, desc.isWrite);
	if (desc.pIdx)
	{
		hr = CreateIndexBuffer(desc.pIdx, desc.idxSize, desc.idxCount);
	}
	m_desc = desc;

	rsize_t vtxMemSize = desc.vtxSize * desc.vtxCount;
	void* pVtx = new char[vtxMemSize];
	memcpy_s(pVtx, vtxMemSize, desc.pVtx, vtxMemSize);
	m_desc.pVtx = pVtx;
	rsize_t idxMemSize = desc.idxSize * desc.idxCount;
	void* pIdx = new char[idxMemSize];
	memcpy_s(pIdx, idxMemSize, desc.pIdx, idxMemSize);
	m_desc.pIdx = pIdx;


}
MeshBuffer::~MeshBuffer()
{
	delete[] m_desc.pIdx;
	delete[] m_desc.pVtx;
	SAFE_RELEASE(m_pIdxBuffer);
	SAFE_RELEASE(m_pVtxBuffer);
}

HRESULT MeshBuffer::CreateVertexBuffer(const void* pVtx, UINT size, UINT count, bool isWrite)
{
	//--- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pVtx;

	//--- 頂点バッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuffer);

	return hr;
}

HRESULT MeshBuffer::CreateIndexBuffer(const void* pIdx, UINT size, UINT count)
{
	// インデックスサイズの確認
	switch (size)
	{
	default:
		return E_FAIL;
	case 2:
	case 4:
		break;
	}

	// バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	// インデックスバッファ生成
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIdxBuffer);

	return hr;
}

void MeshBuffer::Draw(int count)
{
	ID3D11DeviceContext* pContext = GetContext();
	UINT stride = m_desc.vtxSize;
	UINT offset = 0;

	pContext->IASetPrimitiveTopology(m_desc.topology);
	pContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &stride, &offset);

	// 描画
	if (m_desc.idxCount > 0)
	{
		DXGI_FORMAT format;
		switch (m_desc.idxSize)
		{
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		}
		pContext->IASetIndexBuffer(m_pIdxBuffer, format, 0);
		pContext->DrawIndexed(count ? count : m_desc.idxCount, 0, 0);
	}
	else
	{
		// 頂点バッファのみで描画
		pContext->Draw(count ? count : m_desc.vtxCount, 0);
	}

}

HRESULT MeshBuffer::Write(void* pVtx)
{
	if (!m_desc.isWrite) { return E_FAIL; }

	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;

	// データコピー
	hr = pContext->Map(m_pVtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (SUCCEEDED(hr))
	{
		rsize_t size = m_desc.vtxCount * m_desc.vtxSize;
		memcpy_s(mapResource.pData, size, pVtx, size);
		pContext->Unmap(m_pVtxBuffer, 0);
	}
	return hr;
}

MeshBuffer::Description MeshBuffer::GetDesc()
{
	return m_desc;
}