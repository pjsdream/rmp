#include <rmp/renderer/mesh/mesh_loader.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

namespace rmp
{
MeshLoader::MeshLoader(const std::string& filename)
{
  future_mesh_ = std::async(std::launch::async, [filename]()
  {
    Mesh mesh;

    Assimp::Importer assimp_importer{};
    const aiScene* scene =
        assimp_importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (scene != 0)
    {
      aiMesh* assimp_mesh = scene->mMeshes[0];

      mesh.vertex_buffer.reserve(assimp_mesh->mNumVertices);
      std::copy((float*) assimp_mesh->mVertices,
                (float*) (assimp_mesh->mVertices + assimp_mesh->mNumVertices),
                std::back_inserter(mesh.vertex_buffer));

      mesh.normal_buffer.reserve(assimp_mesh->mNumVertices);
      std::copy((float*) assimp_mesh->mNormals,
                (float*) (assimp_mesh->mNormals + assimp_mesh->mNumVertices),
                std::back_inserter(mesh.normal_buffer));

      if (assimp_mesh->HasTextureCoords(0))
      {
        mesh.texture_buffer.resize(assimp_mesh->mNumVertices * 2);
        for (int i = 0; i < assimp_mesh->mNumVertices; i++)
        {
          mesh.texture_buffer[i * 2 + 0] = assimp_mesh->mTextureCoords[0][i][0];
          mesh.texture_buffer[i * 2 + 1] = 1 - assimp_mesh->mTextureCoords[0][i][1];
        }

        auto material = scene->mMaterials[0];
        aiString path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

        mesh.texture_filename = getDirectory(filename) + "/" + path.C_Str();
      }

      mesh.face_buffer.resize(assimp_mesh->mNumFaces * 3);
      for (int i = 0; i < assimp_mesh->mNumFaces; i++)
      {
        mesh.face_buffer[i * 3 + 0] = assimp_mesh->mFaces[i].mIndices[0];
        mesh.face_buffer[i * 3 + 1] = assimp_mesh->mFaces[i].mIndices[1];
        mesh.face_buffer[i * 3 + 2] = assimp_mesh->mFaces[i].mIndices[2];
      }
    }

    return mesh;
  });
}

bool MeshLoader::ready()
{
  using namespace std::literals::chrono_literals;
  return future_mesh_.valid() && future_mesh_.wait_for(0s) == std::future_status::ready;
}

Mesh MeshLoader::get()
{
  return future_mesh_.get();
}

std::string MeshLoader::getDirectory(const std::string& filename)
{
  return filename.substr(0, filename.find_last_of('/'));
}
}
